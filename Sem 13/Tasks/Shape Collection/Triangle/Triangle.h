#pragma once

#include "Shape.h"

class Triangle : public Shape
{

public:
	Triangle(int, int, int, int, int, int);
	double  getArea() const override;
	double getPer() const override;
	bool isPointIn(int, int) const override;
	Shape* clone() const override;

};