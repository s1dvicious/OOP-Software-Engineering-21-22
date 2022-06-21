#include"Rectangle.h"
#include<algorithm>

Rectangle::Rectangle(double x1, double y1, double x3, double y3) :Shape(4) {

	setPoint(0, Point(x1, x1));
	setPoint(1, Point(x1, y3));
	setPoint(2, Point(x3, y3));
	setPoint(3, Point(x3, y1));

}

double Rectangle::getPerimeter()const {

	return (2 * (getPointAtIndex(0).getDist(getPointAtIndex(1))
		+ getPointAtIndex(0).getDist(getPointAtIndex(3))));

}

double Rectangle::getArea()const {

	return (getPointAtIndex(0).getDist(getPointAtIndex(1)) * 
		getPointAtIndex(0).getDist(getPointAtIndex(3)));

}

bool Rectangle::isPointIn(double x, double y)const {

	Point toCheck(x, y);

	return((toCheck.x >= std::min(getPointAtIndex(0).x, getPointAtIndex(3).x)
		&& toCheck.x <= std::max(getPointAtIndex(0).x, getPointAtIndex(3).x) &&
		toCheck.y >= std::min(getPointAtIndex(0).y, getPointAtIndex(3).y) &&
		toCheck.y <= std::max(getPointAtIndex(0).y, getPointAtIndex(3).y)));

}