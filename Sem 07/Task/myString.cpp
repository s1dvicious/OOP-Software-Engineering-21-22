#include "myString.h"
#include<cstring>
#pragma warning(disable:4996)
void myString::copyFrom(const myString& other) {
	str = new char[other.size+1];
	strcpy(str, other.str);
	size = other.size;
}

void myString::free() {
	delete[] str;
	size = 0;
}

myString::myString() {
	str = new char('\0');
	size = 1;
}

myString::~myString() {
	delete[] str;
}

myString::myString(const myString& toCopy) {
	copyFrom(toCopy);
}

myString& myString::operator=(const myString& rhs) {

	if (this != &rhs) {
		free();
		copyFrom(rhs);
	}

	return *this;
}

myString::myString(const char* str) {
	
	this->str = new char[strlen(str) + 1];
	strcpy(this->str, str);
	size = strlen(str);
}

void myString::concat(const myString& rhs) {
	char* temp = new char[this->size + rhs.size + 1];
	strcpy(temp, this->str);
	strcat(temp, rhs.str);

	free();
	this->str = temp;
	this->size = strlen(str);
}

size_t myString::getSize()const {
	return size;
}

const char* myString::c_str()const {
	return str;
}