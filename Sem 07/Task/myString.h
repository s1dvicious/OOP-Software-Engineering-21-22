#ifndef MYSTRING_H
#define MYSTRING_h

class myString {
	char* str;
	size_t size;

	void copyFrom(const myString&);
	void free();
public:

	myString(const char*);

	//Big Four
	myString();
	~myString();
	myString(const myString&);
	myString& operator=(const myString&);

	void concat(const myString&);

	size_t getSize()const;
	const char* c_str()const;
};

#endif
