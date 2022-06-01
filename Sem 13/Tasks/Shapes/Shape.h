#pragma once

class Shape {

protected:

	struct Point {

		double x;
		double y;

		Point();
		Point(double, double);

		double getDist(const Point& other)const;
	};
	const Point& getPointAtIndex(size_t)const;

private:

	Point* points;
	size_t pointsCount;

	void copyFrom(const Shape&);
	void free();

public:

	Shape(size_t);

	Shape();
	Shape(const Shape&);
	Shape& operator=(const Shape&);
	virtual ~Shape(); //!!

	void setPoint(size_t index,const Point&);

	//Pure virtual functions!
	virtual double getPerimeter()const =0;
	virtual double getArea()const = 0;
	virtual bool isPointIn(double x, double y)const = 0;
};