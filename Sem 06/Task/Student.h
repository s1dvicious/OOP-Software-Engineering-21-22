#pragma once

class Student {
	char* name;
	int age;

	void copy(const Student&);
	void free();
public:

	Student();
	Student(const char*, int);

	Student(const Student&);
	Student& operator=(const Student&);
	~Student();

	void setName(const char*);
	void setAge(int);

	const char* getName()const;
	int getAge() const;


	void print()const;

};
