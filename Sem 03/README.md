##  Потоци и Файлове (част 1). Текстови файлове.
IO в C++ се базира изцяло върху стриймовете, които са последователности от байтове данни влизащи в и излизащи от програмта. При операциите за вход, байтовете идват от източник за вход (клавиатура, файл, мрежа или друга програма) в самата програма. При операциите за изход, байтовете данни излизат от програмата и се "вливат" във външно "устройство" (конзола, файл мрежа или друга програма). Потоците служат като посредници между програмите и самите IO устройства по начин, който освобождава програмиста от боравене с тях.

  ![enter image description here](https://www3.ntu.edu.sg/home/ehchua/programming/cpp/images/IOstreams.png)  
  За да извърши вход или изход, една C++ програма:
  * Създава поток;
  * Свързва потока с IO устройството (напр. конзола, клавиатура, файл, мрежа или друга програма);
  * Извършва операции за вход/изход върху потока, посредством операции, дефинирани върху "интерфейса" на стрийма по начин, независещ от избора на IO устройство;
  * Прекъсва връзка с потока;
  * Освобождава потока;    

#####  Пример за работа с поток за стандартен вход (cin)
Стандартния вход по подразбиране е клавиатурата, като обектът от iostream библиотеката, който го достъпва е cin
 ```c++
#include <iostream>

int main()
{
	int a, b;              //declares 
	std::cin >> a >> b;
}
 ```

#####  Пример за работа с поток за стандартен изход (cout)
Стандартния изход по подразбиране е екранът, като обектът от iostream библиотеката, който го достъпва е cout. 
 ```c++
#include <iostream>

int main()
{
	int a = 10;
	int b = 12;
	int c = a + b;

	std::cout << a << " + " << b << " = " << c << std::endl;
}
 ```
 
 ## fstream (потоци за вход/изход от/към файл)  
Специфични операции при потоци. 
- fstream-obj fstr; - създава потоков обект
- fstream-obj fstr(s); - създава потоков обект и го свързва с файл с име s (низ/стринг);
- fstream-obj fstr(s,mode); - създава потоков обект, свързва го с файл с име s в режим на работа mode;
- fstr.open(s); - свързва потока с файл s;
- fstr.open(s,mode) - свързва потока с файл s и задава режим на работа mode;
- fstr.close() - затваря файла, към който fstrm е свързан;
- fstr.is_open() - връща булева променлива, която индикира дали свързаният с fstrm файл е успешно отворен и не е затворен;  
името на един файл може да е string или низ.
  
  като под fstream-obj се подразбира ifstream/ofstream/fstream.
  
  ### Четене от файл. За целта ни е необходимо да:
- Създадем ifstream (поток за вход от файл) обект;
- Да го свържем към файл;
- Да четем от потока;
- Да отвържем от файла (чрез .close()) и да освободим потока;

 ```c++
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream file("myFile.txt");    //Declare an ifstream object file and link it to myFile.txt (which is located in the local directory of the project);
       
	if (!file.is_open())            //file.is_open() returns true if the file is successfuly opened, else we write Error! to the console;
	{
		cout << "Error!" << endl;
		return -1;
	}
	int a, b;                       

	file >> a >> b;                //Reading is performed in a complete analogue to the standart input stream;         

	file.close();                  //Close the file, flush the buffer and disconnect from the stream;
}
```
 
### Един поток може да е в различни състояния.
- bad() - връща true, ако е възникнала грешка при четене от/писане върху стрийм. Ако един поток е "bad", то не могат да се извършват повече операции върху него;
- fail() - връща true, ако е възникнала грешка, но все още могат да се извършват операции върху него;
- eof() - връща true, ако е достигнат края на файла;
- good() - връща true, ако потокът не е в нито едно от трите предишни състояния;  
  
  Извикване на функцията .clear() изчиства всички състояния и слага потока в състояние good (всяко следващо извикване на good() връща true).
  
  Пример за прочитане на цялото съдържание файл:
 ```c++
#include <iostream>
#include <fstream>
using namespace std;

const int BUFF_SIZE = 1024;
int main()
{
	ifstream file("myFile.txt");               //Define the ifstream object;

	if (!file.is_open())                      //If the file has not been opened successfuly - write Error! on the terminal window and terminate the program;
	{
		cout << "Error!" << endl;
		return -1;
	}
	while (!file.eof())                      //do the body operations until the end of the file has been reached;
	{
		char buff[BUFF_SIZE];            //declare 
		file.getline(buff, BUFF_SIZE);
		
		//do something with the line
		cout << buff<< endl;
	}
	file.close();
}
```  
  
### Работа с поток за изход към файл (ofstream)
 ```c++
#include <iostream>
#include <fstream>

using namespace std;

int main()
{
	ofstream file("myFile.txt");

	if (!file.is_open())
	{
		cout << "Error!" << endl;
		return -1;
	}
	int a = 3;
	int b = 10;

	file << a << " " << b << " " << a + b << endl;

	file.close();
}
 ```
  
##  Задачи
	
**[Задача 1](https://github.com/s1dvicious/OOP-Software-Engineering-21-22/blob/main/Sem%2003/Tasks/Task%201/%5B15.03%5D%20Task%201.cpp)**: Напишете програма, която отпечатва собствения си код.  
**[Задача 2](https://github.com/s1dvicious/OOP-Software-Engineering-21-22/tree/main/Sem%2003/Tasks/Task%202)**: Напишете програма, която копира съдържанието на съществуващ вече файл в новосъздаден такъв.   
**[Задача 3](https://github.com/s1dvicious/OOP-Software-Engineering-21-22/tree/main/Sem%2003/Tasks/Task%203)**: Напишете програма,  която чете comma-separated values (**CSV**) файл със студенти **със следните 4 полета**: Първо име, Фамилно име, Имейл, Факултетен номер.
1.  Със стартирането на програмата потребителят да въвежда име на файл, който да бъде зареден в паметта.
2.  Напишете функция, която след зареждане на файла да отпечатва на **стандартния изход** информация за студента при подаден **факултетен номер**.
3.  Напишете функция, която **по подаден факултетен номер и низ**, променя първото име на студента, който има дадения факултетен номер, с подадения низ.
4.  Напишете функцията , която приема низ (име на файл) и запазва студентите в същия формат (**CSV**). Т.е. при повторно пускане на програмата да може да прочете новия генериран файл.

Да се реализира прост интерфейс, с който да се извикват написаните фунцкии през конзолата:

**Пример** (входът от потребителя започва с '>'):

 ```
Open file: 
>students.csv
File successfully opened!
>print 80000
Name = Stefan Velkov, Email: stefan@yahoo.com, FN: 80000
>edit 80000 Krum
>print 80000
Name = Krum Velkov, Email: stefan@yahoo.com, FN: 80000
>save students2.csv
file students2.csv successfully saved!
```

