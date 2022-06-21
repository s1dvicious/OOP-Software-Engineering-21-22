#include"Triangle.h"
#include<iostream>
#include<limits>

Triangle::Triangle(double x1, double y1, double x2, double y2, double x3, double y3)
	:Shape(3) {

	setPoint(0, Point(x1, y1));
	setPoint(1, Point(x2, y2));
	setPoint(2, Point(x3, y3));

}

double Triangle::getPerimeter()const {

	return getPointAtIndex(0).getDist(getPointAtIndex(1)) +
		getPointAtIndex(1).getDist(getPointAtIndex(2)) +
		getPointAtIndex(2).getDist(getPointAtIndex(0));

}

double Triangle::getArea()const {

	double halfP = getPerimeter() / 2;
	double sideA = getPointAtIndex(0).getDist(getPointAtIndex(1));
	double sideB = getPointAtIndex(1).getDist(getPointAtIndex(2));
	double sideC = getPointAtIndex(2).getDist(getPointAtIndex(0));

	return sqrt(halfP * (halfP - sideA) * (halfP - sideB) * (halfP - sideC));

}

bool Triangle::isPointIn(double x, double y)const {

	double triangleSum = 0;
	Point pt1 = getPointAtIndex(0);
	Point pt2 = getPointAtIndex(1);
	Point pt3 = getPointAtIndex(2);

	triangleSum += Triangle(pt1.x,pt1.y,pt2.x,pt2.y,x, y).getArea();
	triangleSum += Triangle(pt2.x, pt2.y, pt3.x,pt3.y,x,y).getArea();
	triangleSum += Triangle(pt3.x, pt3.y, pt1.x, pt1.y, x, y).getArea();

	return std::abs(getArea() - triangleSum) <= 0;
}