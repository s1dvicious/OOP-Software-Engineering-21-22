#include "Circle.h"

const double PI = 3.1415;

Circle::Circle(double x, double y, double radius) : Shape(1), radius(radius) {

	setPoint(0, Point(x, y));

}

double Circle::getPerimeter()const {

	return 2 * PI * radius;

}

double Circle::getArea()const {
	
	return PI * radius * radius;

}

bool Circle::isPointIn(double x, double y)const {

	return getPointAtIndex(0).getDist(Point(x, y)) <= radius;

}