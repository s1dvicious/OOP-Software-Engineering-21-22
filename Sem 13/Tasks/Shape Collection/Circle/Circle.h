#pragma once
#include "Shape.h"

class Circle : public Shape
{
	double radius;
public:
	Circle(int, int, double);

	double getArea() const override;
	double getPer() const override; 
	bool isPointIn(int, int) const override;
	Shape* clone() const override;
};