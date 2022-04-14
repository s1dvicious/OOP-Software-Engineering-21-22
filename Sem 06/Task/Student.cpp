#include "Student.h"
#include<cstring>
#include<iostream>

#pragma warning(disable:4996)

void Student::copy(const Student& other) {

	name = new char[strlen(other.name) + 1];
	strcpy(this->name, other.name);

	age = other.age;

}

void Student::free() {
	delete[] name;
}

Student::Student(){
	name = new char('\0');
	age = 0;
}

Student::Student(const char* name, int age) {
	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
	this->age = age;
}

Student::Student(const Student& toCopy) {
	copy(toCopy);
}

Student::~Student() {
	free();
}

void Student::print() {
	std::cout << "Name = " << name << ", age = " << age << std::endl;
}

Student& Student::operator=(const Student& rhs) {

	if (this != &rhs) {
		free();
		copy(rhs);
	 }

	return *this;
}
