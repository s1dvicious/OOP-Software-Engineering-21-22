## Структури - представяне в паметта и подравняване.


![enter image description here](https://media.geeksforgeeks.org/wp-content/cdn-uploads/MemoryAlignment1.gif)

Паметта е байт-адресируема, т.е. може да достъпва всеки байт индивидуално. Ако паметта е подредена последователно като една по една клетка с големина 1 байт, то на процесора му биха били необходими 4 memory read цикъла, за да прочете един **int**. Би било по-економично да прочетем всичките 4 байта наведнъж. Затова, паметта бива наредена по групи от 4 байта, както на картинката горе.  
Наредбата в този случай също е последователна, като ако клетка 0 заема адрес **X**, то клетка 1, клетка 2 и клетка 3 заемат адреси **(X+1)**, **(X+2)** и **(X+3)** респективно. Ако един **int** се намира на адрес **X** (където **X=4k** за някое **k**), то на процесора му е необходим един цикъл, за да го прочете. В противен случай, т.е. ако **int**-a се намира на адрес, който не се дели на 4, то на процесора биха му необходими два цикъла, за да го прочете. (_виж картинката долу_)

![Pic 2](https://media.geeksforgeeks.org/wp-content/cdn-uploads/MemoryAlignment2.gif)  

Подравняването на променливите се отнася именно към начина, по който променливите биват разположени в тези клетки. Например, естественото подравняване на един int при 32-битова архитектура е 4 байта. Когато един тип данна е естествено подравнен, на процесорът му е необходим **минимален** брой цикли, за да го прочете.  
Аналогично, естественото подравняване на **short** е 2 байта, т.е. **short**-a може да бъде разположен в една от двойките групи - 0 и 1 или в 2-3. Един **double** заема 8 байта в паметта и са необходими 2 цикъла (при 32 битова архитектура), за да бъде прочетен. При липса на подравняване циклите стават повече от два. Заб., че при 64-битова архитектура **double**-a бива прочетен за един цикъл.  
Структурите се използват за групиране на данни, като всеки член трябва да е естествено подравнен. Б.о.о. нека всяка от структурите в следващите примери да се намира на адрес **0x0000**.

```c++
struct struct_a
{
    char        c;
    short int   s;
} str_a;
 ```
Естественото подравняване на char-a е 1 байт, а на **short** int-a 2 байта. Ако **short**-a бива сложен непосредствено след char-a, то той би започнал на нечетен адрес (противоречие с необходимостта от подравняване на елементите). Затова, компилаторът добавя 1 байт подравняване (празен байт) след **char**-a и **short**-a е сложен на адрес 0x0002. Размерът на структурата в случая е _sizeof(struct_a)=sizeof(char)+1(padding)+sizeof(short)=1+1+2=4_

```c++
struct struct_b
{
    short int   s;  //2 bytes
    char        c;  //1 byte
    int         i;  //4 bytes
} str_b;
```
Добавя се 1 байт подравняване след char-a.  _sizeof(structb)=sizeof(short)+sizeof(char)+1(padding)+sizeof(int)8_;

```c++
struct struct_c
{
    char        c;  //1 byte
    double      d;  //8 bytes
    int         s;  //4 bytes
} str_c;
```
Аналогично, размерът на structc e _sizeof(char)+7(padding)+sizeof(double)+sizeof(int)=1+3+8+4=20_. Да, ама не. Както при примитивните типове данни, структурите също имат естествено подравняване. Например, ако декларираме
```c++
structc arr[3];
```
и б.о.о. нека arr[0] е разположен на адрес **0x0000**. Ако structc заемаше 20 byte-a (0x14), то втория елемент на масива би започнал от адрес (**0x0014**), т.е. double-a на arr[1] би бил разположен на адрес (0x0014+0x1+0x7)=(0x001C), което е 28 в десетична бройна система, което противоречи на естественото подравняване на double-a. За да се избегне това, непосредствено след **int**-a се слагат 4 байт-а подравняване, в следствие на което размерът на структурата става 24 байт-а.  
#### Summary:
- В паметта променливите са разположени в същия ред, в който са декларирани в структурата;
- Подравняването на една структура става по **големината на най-голямата член-данна (даже и в случая на вложена структура)** на структурата (с цел минимизация на подравняването);
- _Неформално_: Всяка променлива трябва да е на байт (ако приемем, че байтовете имат индекс, започвайки от 0), кратен на големината на най-голямата член-данна;

Подравняването е неизбежно. За сметка на това, то може да бъде минимизирано (както отбелязахме вече), като данните биват подредени в нарастващ или намаляващ ред. В тази връзка, човек ако си поиграе с долната структура, т.е. ако размести наредбата на данните в структурата **Test**, то той би получил различни размери. Минималният такъв се достига при сортирани (по байтове) в нарастващ ред елементи.
```c++
#include <iostream>

struct Test{
    char c1;               //1 byte
    char c2;               //1 byte
    double l;              //8 bytes
    short s;               //2 bytes
}test;
```
	

## Файлове (част 2). Позициониране, режими на работа. Двоични файлове.

### Позициониране във файл  
При четене от и писане в файл, данните, които се четат/пишат се указват от специален указател:
 - tellg() - Връща позиция на текущия символ в **потока за четене**
 - tellp() - Връща позиция на текущия символ в **потока за писане**
 - seekg(offset, direction) - премества get-указателя с **offset** на брой позиции, започвайки от позиция **direction** в **потока за четене**;
 - seekg(streampos idx) - премества get-указателя на позиция **idx**;
 - seekp(offset, direction) - премества put-указателя с **offset** на брой позиции, започвайки от позиция **direction** на позиция на **потока за писане**
 - seekp(streampos idx) - премества put-указателя на позиция **idx**;
 
 
 -**offset** : целочислена стойност. Отместването от direction.
 
 -**direction** : Може да заема следите стойностти:

1. ios::beg - началото на файла.
2. ios::cur - текущата позиция във файла.
3. ios::end - края на файла.

### Всеки поток има режим на работа
 ```c++
	stream-obj str("file.txt", <режим на работа1> | <режим на работа2> ... );
	//OR
	stream-obj str;
	str.open("file.txt", <режим на работа1> | <режим на работа2> ... ));
 ```
Режимът на работа е цяло число. Те индикират по какъв начин ще се работи със съответния файл.

| ios         | | Ефект:                                                                                                                           |
|-------------|--|--------------------------------------------------------------------------------------------------------------------------------|
| ios::in     | input | Отваря файл за извличане. Default режим при ifstream. При **binary** режим на работа се подава като режим на работа даже при потоци за извличане                                                                      |
| ios::out    | output | Отваряне на файл за вмъкване. Допуска се вмъкване на произволни места във файла. Ако файлът съществува, съдържанието се изтрива. Default при ofstream. Аналогично, както и при **ios::in** - при **binary** режим на работа се указва |
| ios::ate    | at end | Отваря за вмъкване и установява указателя put в края на файла. Допуска вмъкване на произволни места.                             |
| ios::app    | append | Отваря за вмъкване и установява указателя put в края на файла. Всички вмъквания са в края на файла!                            |
| ios::trunc  | truncate | Ако файлът съществува, съдържанието се изтрива.                                                                                  |
| ios::binary | binary | Превключва режима от текстов в двоичен                                                                                           |
| ios::_Nocreate_ |  | Отваря за вмъкване, само ако файлът с указаното име съществува.        |
| ios::_Noreplace_ |  | Отваря за вмъкване само ако файлът с указаното име не съществува.   |

_Note1:_ режимите на работа **ios::app** и **ios::trunc** не са съвместими (не се използват заедно). При съвместно използване се вдига **failbit** флаг-а на потока.  
_Note2:_ При **ios::app** режим на работа файлът винаги се отваря по default за output.  
_Note3:_ При **ios::out** режим на работа, съдържанието на файла винаги се изтрива. За да избегнем това отваряме файла в режим **ios::app**, като в този случай можем да пишем единствено в края на файла.  

**Пример 1**. Създаваме ofstream поток и му задаваме **ios::app** режим на работа. Всяко вмъкване е в края на файла.
```c++
#include <iostream>
#include <fstream>

int main() {
	
	std::ofstream file("newTest.txt", std::ios::app);
	
	if (!file.is_open()) {
		std::cout << "Error while opening the file.";
		return -1;
	}
	
	file << 33;
	
	file.close();

	return 0;
}
```

### Флагове на състоянията на потока 
| Флаг:| Значение:                                                                      | 
|--------|------------------------------------------------------------------------------|
|bad()   | Има загуба на информация. Някоя операция за четене и писане не е изпълнена. Например ако файлът не е отворен успешно или ако не е останало място за писане/четене |
|fail() |Последната входно/изходна операция е невалидна|
| eof() | Достигнат е края на файла |
|good() | Всички операции са изпълнени успешно|
|clear()| Изчиства състоянието на потока (вече good() ще върне истина)|

**Задача 1** Да се имплементира функция, която приема като параметър име на файл намира големината му (в байтове).

```c++
#include <iostream>
#include <fstream>

size_t getFileSize(std::ifstream& file) {

        size_t currentPosition=file.tellg();  //Save the current position
	
	file.seekg(0, std::ios::end);     //Move the get pointer to the end of the file 
	size_t pos = file.tellg();        //Declare the position variable, initialize it with the current position of the stream (which is the end of the file)
        
	file.seekg(currentPosition);      //Move the get pointer to the initial (currentPosition) position
	return pos;
}

int main() {
	
	std::ifstream file("newTest.txt");

	if (!file.is_open()) {
		std::cout << "Error while opening the file";
		return -1;
	}

	size_t fileSize1 = getFileSize(file);
	std::cout << "The size of the file is " << fileSize1 << " bytes."<<std::endl;

	file.close();

	return 0;
}
```
## Задача 2 (_optional_)
<details>
 <summary> Да се напише функция, която заменя всяко срещане на символ във файл с друг символ. Съдържанието на файла не трябва да се зарежда в паметта.</summary>
	
```c++
#include <iostream>
#include <fstream>

void replaceInFile(char s1, char s2, std::fstream& file) {
	while (!file.eof()) {
		char currSymbol = file.get();

		if (currSymbol != s1) {
			continue;
		}

		file.seekp(-1, std::ios::cur);
		file.put(s2);
		file.flush();
	}

}


int main() {
	std::fstream file("testFile.txt", std::ios::in | std::ios::out);
	
	if (!file.is_open()) {
		std::cout << "Error while opening the file.";
		return -1;
	}

	replaceInFile('l', 'X', file);

	file.close();

	return 0;
}
``` 
</details> 
	
## Двоични файлове.

Използваме функциите:

1. .read(char* memoryBlock, size_t size);
2. .write(const char* memoryBlock, size_t size);

Обърнете внимание, че функцията приема **char***. Ако искаме да запазим променлива от друг вид, ще трябва експлицитно да преобразуваме указателя към тип char* (без значение, че указателят не сочи към елементи от тип char).

### Пример. Писане в двоичен файл
 ```c++
#include <iostream>
#include <fstream>

int main()
{
	std::ofstream file("file.dat");

	int a = 155555;

	f.write((const char*)&a, sizeof(int));

	return 0;
}
 ```
 ### Пример. Четене от двоичен файл
 
  ```c++
#include <iostream>
#include <fstream>

int main()
{
	std::ifstream f("file.dat");

	int a;

	f.read((char*)&a, sizeof(int));

	std::cout << a << endl;

	return 0;
}
 ```
### Съдържанието на двоичния файл:
 ![enter image description here](https://i.ibb.co/G3R72qG/sudurjanie.png "Binary file example")
 
Байтовете се записват в **обратна посока**. Най-старшият байт е последен. Следователно запаментеното число е **00025fa3**, което е точно шестанйсетичния запис на числото **155555**.

### Примери за запазване на структури в двоичен файл

### Пример 1. Запазване на структура, която не използва динамична памет

```c++
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable:4996)

const int MAX_FIELD_LENGTH = 65;

struct Student {
	char name[MAX_FIELD_LENGTH];
	int fn;
	int age;
};


int main() {
	{//write
		Student st;
		strcpy(st.name, "Pesho");
		st.fn = 31479;
		st.age = 24;

		std::ofstream file("student.dat", std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while opening the file.";
			return -1;
		}

		file.write((const char*)&st, sizeof(st));


	}

	{//read
		Student st;
		
		std::ifstream file("student.dat", std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while opening the file.";
			return -1;
		}

		file.read((char*)&st, sizeof(st));

		std::cout << "Name of student = " << st.name << ", FN = " << st.fn << ", age = " << st.age;

		file.close();
	}


	return 0;
}
```

### Пример 2. Запазване на структура, която използва динамична памет

```c++
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable:4996)

struct Student {
	char* name;
	int fn;
	int age;
};

void printStudent(const Student& st) {
	std::cout << "Name " << st.name << ", FN = " << st.fn << ", age = " << st.age << std::endl;
}

Student createStudent(const char* name, int fn, int age) {
	Student temp;

	temp.name = new char[strlen(name) + 1];
	strcpy(temp.name, name);

	temp.fn = fn;

	temp.age = age;

	return temp;

}

void freeStudent(Student& st) {
	delete[] st.name;

	st.age = 0;
	st.name = 0;
}

void saveStudentToFile(std::ofstream& file, const Student& st) {
	size_t nameLength = strlen(st.name);

	file.write((const char*)&nameLength, sizeof(nameLength));
	file.write(st.name, nameLength);

	file.write((const char*)&st.fn, sizeof(st.fn));
	file.write((const char*)&st.age, sizeof(st.age));
}

Student readStudentFromFile(std::ifstream& file) {
	Student temp;

	size_t nameLen;
	file.read((char*)&nameLen, sizeof(nameLen));

	temp.name = new char[nameLen + 1];
	file.read(temp.name, nameLen);
	temp.name[nameLen] = '\0';

	file.read((char*)&temp.fn, sizeof(temp.fn));
	file.read((char*)&temp.age, sizeof(temp.age));

	return temp;
}



int main() {

	{//write
		Student st1 = createStudent("Pesho", 31479, 24);
		Student st2 = createStudent("Ivan", 31480, 25);
		std::ofstream file("output.dat", std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while opening the file";
			return -1;
		}

		saveStudentToFile(file, st1);
		saveStudentToFile(file, st2);

		file.close();
		freeStudent(st1);
		freeStudent(st2);
	}

	{//read
		Student st1;
		Student st2;
		std::ifstream file("output.dat", std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while opening the file";
			return -1;
		}

		st1 = readStudentFromFile(file);
		st2 = readStudentFromFile(file);

		printStudent(st1);
		printStudent(st2);

		freeStudent(st1);
		freeStudent(st2);

		file.close();

	}


	return 0;
}
```

### Пример 3. Запазване на масив от структури, които не използват динамична памет

```c++
#include <iostream>
#include <fstream>
#include <cstring>
#pragma warning(disable:4996)

struct Student {
	char name[30];
	int age;
	int fn;
};

void initStudent(Student& st, const char* name, int age, int fn) {

	strcpy(st.name, name);
	st.age = age;
	st.fn = fn;

}

void saveToFile(const Student* students, size_t studentsCount, std::ofstream& file) {
	
	file.write((const char*)students, studentsCount * sizeof(Student));

}

void printStudent(const Student& st) {
	std::cout << "Name " << st.name << ", FN = " << st.fn << ", age = " << st.age << std::endl;
}

size_t getFileSize(std::ifstream& f) {

	size_t currentPos = f.tellg();
	
	f.seekg(0, std::ios::end);
	size_t size = f.tellg();

	f.seekg(currentPos);

	return size;
}

void readFromFile(Student*& ptr, size_t& studentsCount, std::ifstream& file) {

	size_t fileSize = getFileSize(file);

	studentsCount = fileSize / sizeof(Student);    
	ptr = new Student[studentsCount];
	
	file.read((char*)ptr, fileSize);
}

int main() {
	{//write
		Student* students = new Student[4];

		initStudent(students[0], "Pesho", 22, 2314);
		initStudent(students[1], "Ivan", 24, 3132);
		initStudent(students[2], "Georgi", 25, 31356);
		initStudent(students[3], "Zhelyazko", 21, 3144);

		std::ofstream file("students.dat", std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while opening the file";
			delete[] students;
			return -1;
		}

		saveToFile(students, 4, file);

		file.close();
		delete[] students;
	}

	{//read
		Student* students;
		size_t studentsCount;

		std::ifstream file("students.dat", std::ios::binary);

		if (!file.is_open()) {
			std::cout << "Error while opening the file!";
			return -1;
		}

		readFromFile(students, studentsCount, file);

		for (int i = 0; i < studentsCount; ++i) {
			printStudent(students[i]);

		}

		delete[] students;
		file.close();

	}

	return 0;
}
```
