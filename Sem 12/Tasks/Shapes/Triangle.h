#pragma once
#include"Shape.h"

class Triangle :public Shape {

public:
	Triangle(double,double,double,double,double,double);

	double getPerimeter()const override;
	double getArea()const override;
	bool isPointIn(double, double)const override;
};