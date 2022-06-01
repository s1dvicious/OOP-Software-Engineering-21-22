#include "Cow.h"

void Cow::sayHello() const
{
	std::cout << "Hello, I am a Cow!" << std::endl;
}

Animal* Cow::clone() const
{
	Animal* newObj = new Mouse(*this); //copy constr of Cow
	return newObj;
}
