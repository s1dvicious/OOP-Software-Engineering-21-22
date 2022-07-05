#pragma once
#include <iostream>

class Shape   // Abstract class - no instances of Shape are allowed!
{
protected:
	struct point
	{
		point() :x(0), y(0){}
		point(int x, int y) :x(x), y(y){}
		int x;
		int y;
		double getDist(const point& other) const
		{
			int dx = x - other.x;
			int dy = y - other.y;

			return sqrt(dx*dx + dy*dy);
		}
	};
	const point& getPointAtIndex(size_t index) const;
private:
	point* points;
	size_t pointsCount;
public:
	Shape(size_t);
	Shape(const Shape&);
	Shape& operator=(const Shape&);
	virtual ~Shape();

	void setPoint(size_t, int, int);

	virtual double getArea() const = 0;
	virtual double getPer()  const = 0; 
	virtual bool isPointIn(int, int) const = 0;
	virtual Shape* clone() const = 0;
private:
	void copyFrom(const Shape& other);
	void free();
};