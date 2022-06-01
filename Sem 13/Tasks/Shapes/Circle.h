#pragma once
#include "Shape.h"

class Circle : public Shape {

	double radius;

public:

	Circle(double, double, double);

	double getPerimeter() const override;
	double getArea() const override;
	bool isPointIn(double, double) const override;

};
