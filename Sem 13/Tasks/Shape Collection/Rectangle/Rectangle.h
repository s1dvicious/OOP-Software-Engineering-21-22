#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(int, int, int, int);
	double getArea() const override;
	double getPer() const override;
	bool isPointIn(int, int) const override;
	Shape* clone() const override;
};