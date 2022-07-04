# Наследяване

Да разгледаме програма, която "моделира" служители на една фирма. Такава фирма може да има следните структури

```c++
struct Employee {

string firstName, secondName; 
double salary;

};
```

а също и мениджър

```c++
struct Manager {

	Employee emp;                   //A manager is an employee, hence this member
	vector<Employee*> group;   //People managed, vector of pointers to other employees
	short level;
	
//additional functionalities...
};
```
Един мениджър е също и служител - именно тази характеристика се държи и в член-данната emp от тип **Employee**, която се съдържа в един **Manager** обект. Четейки кода това би било очевидно на нас, но на компилатора не се дава абсолютно никаква индикация, че **Manager** **Е** (**is a**) **Employee**. Един указател към **Manager** ```Manager*```  не е указател към **Employee** ```Employee*```. Добре де, ами ако някой мениджър ръководи други мениджъри? С други думи, не можем да сложим **Manager** сред вектора от указатели към **Employees** без писане на специален код. За да избегнем това писане, правилният подход е експлицитно да заявим, че един **Manager** **е** (is a) **Employee** : 

```c++
struct Manager: public Employee{

std::vector<Employee*> group;
short level;

}
```
Т.е. **Manager** наследява **Employee** и обратно - **Employee** е базов клас за **Manager**.  
Наследявайки **Manager** от **Employee** по този начин дефинира **Manager** като подтип на **Employee**. Например вече можем да правим следното 

```c++
Manager m, m1;
Employee e1;
m.group.push_back(&e1);
m.group.push_back(&m1);
```
Един **Manager** е **Employee**, следователно ```Manager*``` може да се използва като ```Employee*```. Аналогично и при референциите. Обаче, един **Employee** не е непременно **Manager**, т.е. обратното не е в сила.  

```c++
Manager mm;
Employee ee;

Employee* pe = &mm;    //OK, every Manager is an Employee
Manager* pm = &ee;     //error: not every Employee is a manager
```

След наследяване нещата изглеждат по следния начин 

![enter image description here](https://i.imgur.com/cl1eQWE.jpg)

т.е. при създаване на обект от тип **Manager** се създава обект от тип **Employee**, който е част от него. Т.е. **Manager** има член-данни от класа **Employee**, а в допълнение към това и свои собствени новодефинирани членове (**group**, **level**, etc.).  

## Какво се наследява от базовия клас?

Има три вида наследяване - **public, private** и **protected**. Видът наследяване определя видимостта на наследените членове в производния клас

![enter image description here](https://raw.githubusercontent.com/Justsvetoslavov/Object-oriented_programming_FMI_2021-2022/main/Sem.%2011/img/visibility.png)

Т.е. 
- Всички член-данни и член-функции, които са **private** в базовия клас, винаги се наследяват като **private** (и нямаме директен достъп до тях)
- Ако наследим някой клас като **private**, всички член-данни на родителския клас ще бъдат наследени като **private**
- **protected** ни позволява на тези член-данни да са видими за производните класове, но не и извън тях

Нека в допълнение, класовете **Employee** и **Manager** да притежават и член-функции за принтиране

```c++
class Employee{

string firstName, secondName;
double salary;

public:

string fullName() const {
		return (firstName + " " + secondName);
}
	
void print() const {
		std::cout << fullName()<<", salary = "<<salary<<std::endl;
}
};

class Manager: public Employee{

std::vector<Employee*> group;
short level;

public:

void print() const;

};
```
Производния клас има достъп до **public** и **protected** елементите на базовия - все едно са дефинирани в производния. Например

```c++
void Manager::print() const{

		std::cout<<fullName();
		
}
//prints the first and second name of the manager (defined in the Employee class from which we're deriving)
```
Обаче производния клас няма достъп до **private** членовете на базовия клас 
```c++
void Manager::print() const{

		std::cout<<firstName<<" "<<secondName; //ERROR, access violation!
		//...
}
```
Тази версия на **print()** няма да се компилира, т.к. firstName не може да бъде достъпен в **Manager::print()**.  
Добре де, ами ако член функция на производен клас имаше достъп до **private** членовете на базовия клас? Тогава концепцията за капсулация директно губи значение - едно простичко наследяване би ни позволило да достъпим и **private** частите на съответния клас. Затова, ако искаме да дадем достъп до някой член (препоръчително е член данните да са **private**) - слагаме **protected**.  
Най-чистото (засега) решение на този проблем е производния клас да използва единствено **public** членовете на базовия клас. Например  

```c++
void Manager::print() const{

		Employee::print();  //print Employee information
		std::cout<<level;   //print Manager-specific information
{
```
Забележка, че използването на scope-resolution оператора **::** е от значение (в противен случай влизаме в редица рекурсивни извиквания на print()), т.к. **print()** се редефинира (скрива) при **Manager**. 

## Подаване като параметър във функция
Класове-наследници могат да бъдат подавани като параметри на функции, които приемат обекти от базовия клас. Може да се използва функционалността само от базовия клас.
```c++
class A
{
public:
	int a;
};
class B : public A
{
public:
	int b;
};
void f(A& obj)
{
	obj.a++;
}

void g(A* ptr)
{
	(*ptr).a++;
}

void t(B& obj)
{
	obj.b++;
}

int main()
{
	A obj1;
	B obj2;
	
	f(obj1); //OK!
	f(obj2); //OK!
	
	g(&obj1); //OK!
	g(&obj2); //OK!
	
	t(obj2);  //OK!
	//t(obj1)// not ok!
}
```


## Конструктори и деструктори
Те не се наследяват от базовия клас, но за сметка на това биват преизползвани при инициализация на **base** частта от производния клас (т.е. дефинираните в производния се дефинират като делегиращи).  

- Обектите се създават отдолу-нагоре, т.е. в следната последователност ```Base -> Member -> Derived```, и се унищожават отгоре-надолу, т.е. в следната последователност ```Derived-> Member -> Base```

```c++
class base {
	int x;

public:
	base() :x(0) { std::cout << "base default constructor"<<std::endl; }
	base(int x) : x(x) { std::cout<< "base constructor" << std::endl;  }   
	~base() { std::cout << "base destructor" << std::endl; }
};

class nested {
	char a;

public:
	nested() : a('\0') { std::cout << "nested default constructor" << std::endl; }
	~nested() { std::cout << "nested destructor" << std::endl; }
};

class derived:public base {
	nested obj;

public:
	derived() { std::cout << "derived default constructor" << std::endl; }
	~derived() { std::cout << "derived destructor" << std::endl; }
};
```
Конкретно при този пример, създавайки обект от тип **derived** "частите" се създават в горе-упоменатата последователност. Също забелязваме, че при конструктора по подразбиране на **derived** не се дава индикация кой от двата конструктора на **base** ще бъде извикан, т.е.:

``` Когато наследим клас, без да кажем кой конструктор на наследения клас да се извика, винаги се извиква този по подразбиране на базовия (ако такъв съществува). Ако искаме да извикаме друг, то трябва експлицитно да се укаже кой при инициализиращия списък (т.е. конструкторът на базовия да се дефинира като делегиращ) ```

Например, конкретно при нашия пример имаме 

```c++
Employee(const char* firstName, const char* secondName,short department)
		:firstName(firstName), secondName(secondName), department(department) {}
	

Manager(const char* firstName, const char* secondName, short department, const std::vector<Employee*>& group, short level)
                : Employee(firstName, secondName, department), group(group), level(level){}
```

## Копиране при наследяване

При разписване на конструктора за копиране и оператора за присовяване на клас-наследник, трябва експлицитно да извикваме копиране и за базовия клас.

 ```c++
Manager(const Manager& toCopy) : Employee(toCopy){

		copyFrom(toCopy);    
		
	}

Manager& operator=(const Manager& toCopy) {

		if (this != &toCopy) {

			Employee::operator=(toCopy);
			
			free();
			copyFrom(toCopy);
	  }
}
 ```
 
- Ако НЕ ги дефинираме в Derived класа, компилаторът ще ги създаде автоматично и ще извика версията на базовия клас.
- Ако ги дефинираме в Derived класа, трябва изрично да се извикат базовите (invoke the Base class definition explicitly)
 
`` Важно: правилото голяма 4ка (copy контрол) остава в сила, както и преди - ако генерираните от компилатора такива не вършат работа, което в най-общи линии се случва при заделяне на динамична памет при производния клас, то те се разписват.``
