#pragma once
#include "Animal.h"
class Cow : public Animal
{
public:
	void sayHello() const override;
	Animal* clone() const override;
};
