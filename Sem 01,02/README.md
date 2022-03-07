##  Преговор върху динамична памет
Паметта, която можем да използваме в **C++** най-общо казано се разделя на 3 типа (всъщност те са много повече, но за нашите цели към момента тези 3 са достатъчни):
*	**Статична**:в тази памет се записват статичните/глобалните променливи.

*	**Стекова (stack)**: тя съдържа "локалните" променливи, т.е. онези, които са дефинирани в телата на функции и са същевременно нестатични. 
	
	<ins>**Свойства:**</ins> 
	  * Паметта се заделя в момента на дефиниция на променливите;
	  * Паметта се освобождава в момента на изход от блока (scope-a), в която е дефинирана;
	  * Последно заделената памет се освобождава първа (First in Last out);
	  * Ние нямаме контрол над управлението над паметта
	    * Паметта не може да се освободи по-рано (преди края на блока);
	    * Паметта не може да се освободи по-късно (след края на блока);
	  * Количеството заделена памет е до голяма степен определена по време на компилация;
	
 
*	**Динамична (heap)**: е "свободната" част от паметта, която се използва (<em>динамично</em>) в хода на програмата. 

	<ins>**Свойства:**</ins>
	* Динамичната памет може да бъде заделена и освободена по всяко време на изпълнение на програмата;
	* Областта за динамична памет е набор от свободни блокове памет;
	* Програмата може да заяви блок с произволна големина;
	* Операционната система се грижи за управлението на динамичната памет;  
	  * поддържа „карта“ кои клетки са свободни и кои заети;  
	  * контролира коя част от паметта от коя програма се използва;


Заделянето на динамична памет става посредством оператора **new**, като той връща указател към блока, в който е заделена и синтаксисът е
```c++

<data-type> *ptr=new <data-type>;                   //Allocates a block of memory on the heap for variable of data-type;
delete ptr;                                         //Deallocate the allocated memory;

<data-type> *ptr=new <data-type>(<data-type value>); //Allocates a block memory on the heap for variable of data-type and initializes it with <data-type value>;
delete ptr;                                         //Deallocate the allocated memory;

//Allocate memory for N consecutive blocks of the same type <data-type> on the heap and return a pointer to the first element;
size_t N;
std::cin>>N;
<data-type> *ptr=new <data-type>[N];
//Deallocate the allocated memory via the operator delete[], note that delete[] knows how many elements exactly are to be deleted;
delete[] ptr;
```

**Пример за динамично заделяне на масив**
```c++
size_t N,M;               
std::cin>>N>>M;
int**arr2d=new int*[N];   //Allocate memory for N pointers, every each one of which will point to the first member of a dynamically allocated memory consisting of M consecutive blocks in the heap;
for(int i=0; i<M; ++i){
   arr2d[i]=new int[M];
}
//-- do something with arr2d --

for(int i=0; i<M; ++i)
delete[] arr2d[i];        //Deallocate arr2d[i], where i=0,...,M-1;
delete[] arr2d;           //Deallocate arr2d

```
### [Task 1](https://github.com/s1dvicious/OOP-Software-Engineering-21-22/blob/main/Sem%2001%2C02/Task%201/Transpose_2dArray.cpp)  
Да се напише програма, която прочита от конзолата матрица (<em>динамично заделен двумерен масив</em>) с размер **NxM** и я отпечатва транспонирана.


##  Структури
Структурите са user-defined data type, които ни позволяват да групираме елементи, наричани още членове, от различни типове (и съответно дължина) в една съвкупност. Синтаксисът за създаване на структура е
```c++
struct structureName{
	member1;
	member2;
	...
	memberN;
};
```
 където memberK са съответните елементи (примитивни data type-ове). Забележете, че в края на блок-а има точка запетая.  
 
 **Пример1**: Имаме някаква компания. Компанията пък служители. Те се характеризират със своите - име, възраст и заплата. Тогава нашият нов тип **employee** би изглеждал по следния начин
   ```c++
 struct employee{
std::string name;
int age;
double salary;
 };
  ```
 
 
**Пример 2**: Разглеждаме обект кутия. Кутиите характеризираме с техните: широчина, височина и дължина, инак реч на английски: width, height и length. Тогава нашия обект има вида
  ```c++
 struct Box {
double width;
double height;
double length
 };
  ```

###  Деклариране и инициализация на обекти от новия тип
Декларацията на обект става както при декларация на какъвто и да е примитивен тип данна
 ```c++
Box A,B,C; //Default values are given to the elements of A;
```
или непосредствено след самата дефиниция на структурата
 ```c++
struct Box {
double width;
double height;
double length
 }A,B,C;
```
като в този случай новосъздадените обекти A,B и C са глобални.  

След декларация на обект от новия тип, елементите се достъпват (свободно) посредством оператора **(.)**, след което например могат да бъдат инициализирани
 ```c++
Box one;
one.width=3.5;
one.height=3;
one.length=5.5;
```
като самата инициализация може алтернативно да се извърши и посредством
 ```c++
Box one={3.5,3,5.5};
```

###  Подаване като параметър във функции
Както и примитивните типове данни, новосъздадените обекти могат да се подават като параметър във функции.  
Ако не искаме да променяме обекта го подаваме по **константна референция.**
 ```c++
double calculateVolume(const Box& b){
  return b.width*b.height*b.length;
}
```
или ако искаме да работим директно върху аргумента (без да създаваме копие) го подаваме по референция
   
```c++
void readBox(Box& b){
std::cin>>b.width>>b.height>>b.length;
}
```
и съответно можем да го подаваме по копие
```c++
void printBox(Box b){
std::cout<<"Width="<<b.width<<", height="<<b.height<<", length=""<<b.length<<std::endl;
}
```
###  Влагане на структури
Структурите могат да се влагат и в други структури, например нека в допълнение към горе-описаните си характеристиките всеки служител притежава и кутия. Важно е вложените структури да бъдат дефинирани преди тези, в които се влагат, в противен случай гърмим.
```c++
struct Box {
double width;
double height;
double length
 };
 
 struct employee{
std::string name;
int age;
double salary;
Box empl_box;
 };
```
и инициализацията и достъпването до елементите на **empl_box** стават аналогично 
```c++
employee some_guy;
some_guy.name="Pesho";
some_guy.age=21;
some_guy.salary=1000;       //:(
some_guy.empl_box.width=3.5; 
some_guy.empl_box.height=3;
some_guy.empl_box.length=5;

```
или алтернативно за инициализацията можем да постъпим така
```c++
employee some_guy;
some_guy={"Pesho", 21, 1000,{3.5,3,5}};
```

###  Указатели (pointers) към обекти от новодефинирания тип и динамично заделяне на памет
Структурите могат да бъдат сочени от указатели от същия тип, като за стойност указателят държи адреса на първия й елемент
```c++
Box b={3.5,3,5.5}; //Initialize b
Box*ptr=&b;        //the adress of b is assigned to ptr;

std::cout<<ptr<<" "<<&b.width;    //prints the same adresses;
```
В случая при дереферериране се използва оператора **(->)**, т.е.
```c++
std::cout<<ptr->width;
//or equivalently through direct dereferencing
std::cout<<(*ptr).width;
```
можем да създаваме и (статични) масиви от новодефинирания тип
```c++
Box boxes[50]; //Creates 50 instances of the newly defined type;
for(int i=0; i<50; ++i){
readBox(boxes[i]);
}
```
или динамично (с уговорка за освобождаване в последствие) отново чрез операторите **new** и **delete[]**
```c++
size_t N;       //Declares the amount of boxes;
std::cin>>N;      
Box*b=new Box[N]; //Allocate memory for N instances of our newly defined type;
//initialize the parameters of the boxes;
for(int i=0; i<N; ++i){
readBox(boxes[i]);
}
//--do something with the box objects--
delete[] b;
return 0;
```  
### [Task 2](https://github.com/s1dvicious/OOP-Software-Engineering-21-22/blob/main/Sem%2001%2C02/Task%202/Triangles.cpp)
Въвежда се цяло число **N**  и после **N** тригъгълника в равнината, определени от 3 точки (6 координати).Отпечатайте тригълниците **сортирани по лицата им.**  
За целите на сортировката ще използваме по-простичък алгоритъм, измежду **Selection Sort/Bubble Sort**. Разглеждаме масива **areas** с **N** на брой елемента, следвайки задачата. Да отбележим, че всяка размяна (swap) на лица (в масива **areas**) трябва да се отрази и при триъгълниците (**tr**).

<details>
  <summary>Selection Sort</summary>
  
  Итерираме по **i=0,...N-1**. На **i**-та итерация определяме минимален елемент (в случая индекса му min_index) измежду елементите в подмасива **{areas<sub>i+1</sub>,...,areas<sub>N-1</sub>}** и го разменяме с **areas<sub>i</sub>**, в случай, че **areas<sub>i</sub>>areas<sub>min_index</sub>**. В противен случай не ги разменяме.  
	
```c++
void selectionSort(triangle* tr, double* areas, int N){
 int min_index;
 for(int i=0; i<N; ++i){
  min_index=i;
    for(int j=i+1; j<N; ++j){
      if(arr[j]<arr[min_index])
        min_index=j;
    }
    if(min_index!=i){
    swap_areas(ar,i, min_index);
    swap_triangle(tr,i,min_index);
    } 
  }
}
```
</details>

<details>
  <summary>Bubble Sort</summary>
  
  Идеята е да обхождаме масива, т.е. итерираме по **i=1,...,N-1**, като на всяка итерация държим булева променлива **swapped**, чиято стойност в началото е инициализирана като **false**. За всяко **i** сравняваме **areas[i-1]** и **areas[i]** - ако **area[i-1]>areas[i]**, то разменяме стойностите им и слагаме **swapped=true**. Тази процедура продължава докато не излезнем от итерацията със стойност **false** на **swapped**, т.е. ако се е оказало, че масивът като редица е наистина растящ.  

```c++
void bubbleSort(double* areas, triangle* tr, int len) {
	bool swapped=true;
	while (swapped) {
		swapped = false;
		for (int i = 1; i < len ; ++i) {
			if (areas[i-1] > areas[i]){
				swap_areas(areas, i-1, i);
				swap_triangle(tr, i-1, i);
				swapped = true;
		    }
		}
	}
}
```
</details>  
	
## Обединения (union)
**Union**-ът е тип структура, т.е. също групира различни типове данни, като главната особеност при него е количеството памет, което използва. Начинът за създаване на **union** е 
```c++
union unionName{
  member1;
  member2;
  ...
  memberN;
};
```
Като синтаксис наследяваме всичко, засегнато при структурите - начин за декларация,инициализация, подаване като параметър и т.н., с уговорката, че заменяме **struct** с **union**.  
Както отбелязахме, ключова характеристика на обединенията е количеството памет, което използват. Променливите в един **union** са разположени на едно и също място в паметтта, като размерът му е равен на размера на най-голямата му променлива. В тази връзка, във всеки един момент може да се използва само една променлива от състава на обединението и при инициализация на коя-да е такава всички останали променливи стават **undefined**.  
  
### Пример
```c++
union myUnion{
char ch;   //1 byte
short b;  //2 bytes;
int c;    //4 bytes
};

int main(){
	
myUnion un;
	
std::cout<<sizeof(un)<<std::endl;
//Prints 4, i.e. the size in bytes of an int (which is un's largest size-wise component);
	
un.ch='c'; 
//The values of elements b and c in my_un become undefined once ch has been initialized;
	
std::cout<<un.ch<<" "<<un.b<<" "<<un.c<<std::endl;
//prints c garbage garbage
	
std::cout<<(void*)&un.ch<<" "<<&un.b<<" "<<&un.c;    
//The adresses of ch,b and c respective to **un** are the same, since myUnion is a union;

return 0;
}

```
![enter image description here](https://camo.githubusercontent.com/47ecfa56be7126482573129cb364933c78224482ba3365af76f940805b3322e5/68747470733a2f2f692e6962622e636f2f346d366d354d672f756e696f6e2e706e67)
