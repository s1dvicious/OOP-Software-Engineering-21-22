# Член-функции. Конструктори и деструктор. Модификатори за достъп. Капсулация.

## Член-функции.
Досега все сме подавали новодефинирани типове (класове/структури) като аргументи във функция - било то по копие, референция или константна референция:
 ```c++
struct Point
{
	int x;
	int y;
};
bool isInFirstQuadrant(const Point& p)
{
	return p.x >= 0 && p.y >= 0;
}

 ```
Тази функция може и да бъде дефинирана в scope-a на класа
 ```c++
struct Point
{
	int x;
	int y

	bool isInFirstQuadrant()
	{
		return x >= 0 && y >= 0;
	}	
};

//or outside the class, via the scope resolution operator (::)

struct Point
{
	int x;
	int y

	bool isInFirstQuadrant();
	
};

//
bool Point::isInFirstQuadrant(){
return x>=0 && y>0;
}

int main(){
 Point pt(2,2);
 std::cout<<pt.isInFirstQuadrant();     //call the isInFirstQuadrant() function on object pt
}
 ```
т.е. класовете могат да съдържат и член-функции. Както ще споменем малко по-нататък, компилаторът процесира класовете на две стъпки - първо се компилират декларациите на самите функции, след се процесират телата на член-функциите, ако има такива. Точно затова може да се разделят декларациите и дефинициите на член-функциите, т.е. дефинициите могат да се намират и извън "scope-a" на класа, като при дефиниция извън се използва scope resolution operator-а **(::)**.  
Важен детайл е, че при член-функциите имаме достъп до компонентите на класа без да се указва самия обект експлицитно, т.е. се използва обекта, върху който е била извикана функцията.  
Те достъпват обекта, върху който са извикани чрез допълнителен, имплицитен параметър наречен **this** (указател). Когато извикваме член функция, **this** бива инициализиран с адреса на обекта, върху който тя е извикана. Например, извиквайки
```c++
pt.isInFirstQuadrant();
```
компилаторът подава адреса на **pt** на **this** в isInFirstQuadrant(). Тъй като предназначението на **this** е винаги да сочи към обекта, върху който е извикана самата функция, то той е **const** указател.  
Компилаторът автоматично и скрито от нас превежда член-функциите, така че
- да получава **this** като първи параметър
- всяка компонента на обекта в тялото се достъпва чрез **this**.  
Например
```c++
bool Point::isInFirstQuadrant()
	{
		return x >= 0 && y >= 0;
	}
```
се превежда в 
```c++
bool Point::isInFirstQuadrant(Point* const this){     
//remember since this is a pointer (const) to Point we use the -> operator instead, which is equivalent to (*this).member;
return this->x >= 0 && this->y >= 0;
}
```
_Като забележете, че **this** е const указател към Point, т.е. не можем да меним **this**, но можем да променяме обекта, който е сочен от него (четем декларациите на указателите отдясно наляво)._  
и съответно 
```c++
pt.isInFirstQuadrant();
```
се превежда в 
```c++
Point::isInFirstQuadrant(&pt);
```

## Константни член-функции
Това са член-функции, които не правят промени върху обекта, върху който те са извикани.  
Една константна член-функция бива индикирана чрез **const** суфикс след листа й от параметри. Например 
```c++
struct obj{
void inspect() const;   //This member-function promises not to change *this
void mutate();          //This member-function might change *this
};

void Test(obj& changeable, const obj& unchangeable){
changeable.inspect();   // Okay: doesn't change a changeable object
changeable.mutate();    // Okay: changes a changeable object
unchangeable.inspect(); // Okay: doesn't change an unchangeable object
unchangeable.mutate();  // ERROR: attempt to change unchangeable object
}
```
**const** индикира, че **this** е указател към **const**. Член-функции, които използват **const** по този начин не могат да променят обекта, върху който са извикани!  
Те могат да бъдат извиквани от константни обекти.
 
## Конструктори и деструктор.
Всеки клас дефинира как обекти от неговия тип биват инициализирани. Те контролират тази инициализация чрез дефиниране на една или повече специални член-функции, които се грижат за това - **конструктори**. Предназначението на един конструктор е да инициализира данните на един обект, а също и да гарантира, че преди да започне да се работи с обекта, той е във валидно състояние. Те се извикват при създаване на обект.  
Те имат същото име като класа, нямат **return** type. Като едни функции, те имат (възможно и празен) лист от параметри и (възможно и празно) тяло, а за разлика от други - те не биват дефинирани като **const** член-функции, т.к. самият обект приема своята "константност" едва след като конструктора не завърши с инициализацията. Следователно, конструкторите могат да бъдат извиквани върху константни обекти.  
- При липсата на дефиниран(**и**) конструктор(**и**), компилаторът автоматично създава специален такъв - **конструктор по подразбиране**. Той не приема аргументи;
- Той задава **default**-ни стойности на член данните;
- Една от причините да се налага сами да дефинираме този конструктор е (а също и други такива), че автоматично създаденият такъв невинаги прави това, което бихме искали;
- Друга причина е, че компилаторът невинаги успява да създаде такъв;

### Конструктор по подразбиране (без параметри)
- Извиква се при декларация на обект без параметри;
- Инициализира обекта с "празни", но валидно стойности;
```c++
struct Point{
   int x;
   int y;
   
   Point(){//initialize this->x and this->y with their default values;
   x=0;
   y=0;
   }
};
--//--
Point pt1;   //Calls the default constructor of Point
```
или можем да инициализираме директно чрез т.нар. **initializer list** (инициализиращ списък), който задава начални стойности на една или повече от данните, т.е. 
```c++
struct Point{
   int x;
   int y;
   
   Point():x(0),y(0) {}
};
```
_Забележка, че инициализиращ лист винаги може да се извика даже и при непразно тяло на конструктора;_  
Членове, които не присъстват в инициализиращия списък биват инициализирани чрез техния вътрешен инициализатор (конструктор), ако такъв съществува, или приемат default-ни стойности.
### Конструктор с параметри по подразбиране 
- Конструкторите могат да бъдат с подразбиращи се параметри
```c++
struct Point{
   int x;
   int y;
   
   Point(int x, int y){
   this->x = x;         //equivalent to (*this).x=x;
   this->y = y;         //equivalent to (*this).y=y;
   }
};
```

### Деструктор 
Тяхното предназначение е точно обратното на това на конструкторите. Те извършват каквато работа е необходима при унищожаване на обекта, напр. освобождаване на динамично заделена памет.  
- Той е член-функция, като името му е същото като на класа, с префикс (~)
```c++
struct Person
{
    char *name;
    int age;

    Person(const char *name, int age)
    {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        this->age = age;
    };
    ~Person()
    {
        delete[] name;
    }
};
```
- Извиква се при изтриване на обекта:
 -  когато той излезне извън scope-a, в който е деклариран
 -  когато е извикан **delete[]/delete** оператор върху динамично заделени обекти от съответния тип;
 -  Когато не е дефиниран деструктор компилаторът автоматично създава такъв, точно както и при **конструктора за подразбиране**.

### Пример 
```c++
#include <iostream>
#include <fstream>
#include <cstring>

struct Student
{
	char* name;
	int age;

	Student(const char* name, int age)
	{       std::cout<<"Constructor"<<std::endl;
		this->name = new char[strlen(name) + 1];
		strcpy(this->name, name);
		this->age = age;
	}
	
	void print() const
	{       
		std::cout << "Name: " << name << ", age: " << age << std::endl;
	}
	~Student()
	{       
	std::cout<<"Destructor"<<std::endl;
		delete[] name;
	}
};
int main()
{
	Student s("Ivan", 33);                    //Calls the default parameter constructor of Student

	Student* ptr = new Student("Petur", 17);  //Calls the default parameter constructor of Student

	s.print();
	ptr->print();

	delete ptr;                              //Calls the destructor of Student on ptr;
}//calls the destructor of Student on ptr;
```

### Пример - стек на извикванията при вложени класове
```c++

#include<iostream>

class obj_a {
	int a_x;
public:
	obj_a(): a_x(0){
		std::cout << "Constructor a \n";
	}
	~obj_a() {
		std::cout << "Destructor a \n";
	}
};

class obj_b {
	obj_a b_a;
public:
	obj_b(){
		std::cout << "Constructor b\n";
	};
	~obj_b() {
		std::cout << "Destructor b\n";
	}

};

class obj_c {
	obj_b c_b;
public:
	obj_c() {
		std::cout << "Constructor c\n";
	}
	~obj_c() {
		std::cout << "Destructor c\n";
	}

};

int main() {

	obj_c* ptr = new obj_c;   //dynamically allocate memory for obj ptr of type obj_c
	                          //, calls the default constructor of obj_c;
	
	delete ptr;               //deallocate the memory allocated for ptr, call to the destructor of type obj_c;

	return 0;
}
```

 ## Капсулация (encapsulation).
**Капсулацията** (известно още като _"скриване на информация"_) е един от основните принципи в ООП. Тя налага разбиването на един клас на интерфейс и имплементация. Интерфейсът представлява набор от операции, които потребителят може да изпълнява свободно по начин, който не "бърка" в имплементацията. Тя бива скрита (не му се предоставя достъп до нея) и той не се интересува от нея.  
Принципът за **капсулация** ни помага като позволява да определим кои методи и атрибути може да използват потребителите на нашия клас.

 **Модификатор за достъп**:
| Модификатор за достъп: | Достъп:                         |
|------------------------|---------------------------------|
| private                | В текущия клас. Private секциите капсулират имплементацията.                |
| protected              | В текущия клас и *наследниците.   |
|public                 | От всички части на програмата. Public членовете дефинират interface-a на класа. |

*за наследници ще говорим след време...засега не го мислете.  
_Note 1:_ При **struct** модификаторът за достъп по подразбиране е public, а при **class** - private;  
_Note 2:_ Структурите и класовете се различават по Note 1 и семантично - дали ще пишем class/struct. Оттук нататък, след въвеждане на модифкаторите за достъп, ще използваме класове;  

### Селектори и мутатори  
Това са публични член-функции, които се използват за достъпване (**get**) и измяна (**set**) на член-данни, които са декларирани в private/protected секция на един клас. 
**Пример за get-ъри и set-ъри**

 ```c++

#include <iostream>

using namespace std;


struct Student 
{
private:
	int grade;
	int age;
public:
	Student(int grade, int age)
	{
		setGrade(grade);
		setAge(age);
	}
	int getGrade() const
	{
		return grade;
	}
	int getAge() const
	{
		return age;
	}
	void setGrade(int grade)
	{
		if(grade >= 2 && grade <= 6)
			this->grade = grade;
	}
	void setAge(int age)
	{
		if(age >= 0)
			this->age = age;
	}
};

int main()
{
	Student st1(4,25);
	std::cout<<st1.getGrade();
	st1.setGrade(6);
	std::cout<<st1.getGrade();
}

 ```
 т.к. **get**-ърите се изполват за достъпване на стойност на член данна, то те биват дефинирани като константни член-функции!
