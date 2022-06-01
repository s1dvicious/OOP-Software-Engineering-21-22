// KR1Quad.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<string>
#include<vector>
#include<unordered_set>
#include<algorithm>
typedef unsigned short ushort;
template<typename T>
std::ostream& operator<<(std::ostream& os, std::vector<T> vec) {
	for (auto it = vec.begin(); it != vec.end(); ++it)
		os << *it << " ";

	os << std::endl;
	return os;
}

class A {

public:

	A() { std::cout << "A::A()" << std::endl; }
	~A() { std::cout << "A::~A()" << std::endl; }

	void doSomething()const {
		std::cout << "A does something.." << std::endl;
	}
};

class B: virtual public A {

public:

	B() { std::cout << "B::B()" << std::endl; }
	~B() { std::cout << "B::~B()" << std::endl; }
};
class B1 : public B {

public:

	B1() { std::cout << "B1::B1()" << std::endl; }
	~B1() { std::cout << "B1::~B1()" << std::endl; }
};

class C : virtual public A {

public:

	C() { std::cout << "C::C()" << std::endl; }
	~C() { std::cout << "C::~C()" << std::endl; }
};

class C1 : public C {

public:

	C1() { std::cout << "C1::C1()" << std::endl; }
	~C1() { std::cout << "C1::~C1()" << std::endl; }
};




class D : public B1, public C1 {

public:

	D() { std::cout << "D::D()" << std::endl; }
	~D() { std::cout << "D::~D()" << std::endl; }


};

const size_t DEFAULT_CAPACITY = 8;

class Animal {
public:

	virtual void sayHello() const = 0;   //pure virtual

	virtual Animal* clone() const = 0;   //clones an animal object

	virtual ~Animal() {};  //important!!
};

class Cat : public Animal {
public:

	void sayHello()const override {
		std::cout << "Hello, I'm a cat! Meow" << std::endl;
	}

	Animal* clone()const override {
		Animal* newObject = new Cat(*this);

		return newObject;
	}
};

class Dog: public Animal {
public:

	void sayHello()const override {
		std::cout << "Hello, I'm a dog! Woof-woof" << std::endl;
	}

	Animal* clone()const override {
		Animal* newObject = new Dog(*this);

		return newObject;
	}
};

class Cow: public Animal {
public:

	void sayHello()const override {
		std::cout << "Hello, I'm a cow! Moo" << std::endl;
	}

	Animal* clone()const override {
		Animal* newObject = new Cow(*this);

		return newObject;
	}
};


class Farm {

	Animal** animals;
	size_t animalsCount;
	size_t capacity;

	void free();
	void copyFrom(const Farm&);
	void resize();

public:
	Farm();
	Farm(const Farm& other);
	Farm& operator=(const Farm&);
	~Farm();

	void addAnimal(const Animal&);

	void allSayHello()const;
};

int main() {

	Farm myFarm;
	myFarm.addAnimal(Dog());
	myFarm.addAnimal(Cow());
	myFarm.addAnimal(Cow());
	myFarm.addAnimal(Cat());

	myFarm.allSayHello();
}

void Farm::copyFrom(const Farm& toCopy) {

	animals = new Animal * [toCopy.capacity];

	for (size_t i = 0; i < toCopy.animalsCount; ++i) {
		animals[i] = toCopy.animals[i]->clone();   //Hop hop, polymorphism!
	}

	animalsCount = toCopy.animalsCount;
	capacity = toCopy.capacity;

}

void Farm::free() {
	for (size_t i = 0; i < animalsCount; ++i) {
		delete animals[i];   //virtual destructor
	}
	
	delete[] animals;
}

void Farm::resize() {

	Animal** newCollection = new Animal * [capacity *= 2];
	for (size_t i = 0; i < animalsCount; ++i) {
		newCollection[i] = animals[i];    //copy, not clone
	}

	delete[] animals;
	animals = newCollection;
}

void Farm::addAnimal(const Animal& toAdd) {

	if (animalsCount == capacity)
		resize();

	animals[animalsCount++] = toAdd.clone();

}

Farm::Farm() {
	capacity = DEFAULT_CAPACITY;
	animalsCount = 0;

	animals = new Animal * [capacity];
}

void Farm::allSayHello()const {

	for (size_t i = 0; i < animalsCount; ++i) {
		animals[i]->sayHello();
	}
}

Farm& Farm::operator=(const Farm& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Farm::Farm(const Farm& other)
{
	copyFrom(other);
}

Farm::~Farm()
{
	free();
}