#include "Shape.h"
#include<iostream>

Shape::Point::Point():x(0),y(0) {}

Shape::Point::Point(double x, double y):x(x), y(y){}

double Shape::Point::getDist(const Point& other)const {

	double dx = x - other.x;
	double dy = y - other.y;

	return sqrt(dx * dx + dy * dy);
}

const Shape::Point& Shape::getPointAtIndex(size_t index)const {

	if (index > pointsCount || index < 0) throw std::exception("Out of range!");

	return points[index];
}

void Shape::copyFrom(const Shape& toCopy) {
	points = new Point[toCopy.pointsCount];
	pointsCount = toCopy.pointsCount;
}

void Shape::free() {
	delete[] points;
	pointsCount = 0;
}

Shape::Shape(size_t pointsCount) {
	this->pointsCount = pointsCount;
	points = new Point[pointsCount];
}

Shape::Shape() {
	pointsCount = 0;
	points = nullptr;
}

Shape::Shape(const Shape& toCopy) {

	copyFrom(toCopy);

}

Shape& Shape::operator=(const Shape& toCopy) {

	if (this != &toCopy) {
		free();
		copyFrom(toCopy);
	}

	return *this;
}

Shape::~Shape() {
	free();
}

void Shape::setPoint(size_t index, const Point& pt) {

	if (index > pointsCount || index < 0) throw std::exception("Out of range!");

	points[index] = pt;

}


