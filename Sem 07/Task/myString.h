#ifndef MYSTRING_H
#define MYSTRING_h

class MyString
{
	char* str;
	size_t size;

	void copyFrom(const MyString& other);
	void free();

public:

	//default constructors
	MyString();
	MyString(const char*);

	//copy control and destructor
	MyString(const MyString&);
	MyString& operator=(const MyString&);
	~MyString();

	//selectors and mutators
	size_t getSize() const;
	
	//member-functions
	MyString& operator+(const MyString&);
	void concat(const MyString&);
	bool subString(const MyString&) const;
	const char* c_str() const;
};

#endif