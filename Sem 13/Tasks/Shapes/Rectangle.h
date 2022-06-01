#pragma once
#include"Shape.h"

class Rectangle : public Shape {

public:

	Rectangle(double, double, double, double);

	double getPerimeter()const override;
	double getArea()const override;
	bool isPointIn(double,double)const override;

};