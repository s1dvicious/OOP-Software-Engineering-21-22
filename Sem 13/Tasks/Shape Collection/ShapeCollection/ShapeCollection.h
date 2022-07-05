#pragma once
#include "Shape.h"

class ShapeCollection
{
	Shape** shapes;
	size_t shapesCount;
	size_t capacity;
public:
	ShapeCollection();
	ShapeCollection(const ShapeCollection& other);
	ShapeCollection& operator=(const ShapeCollection& other);
	~ShapeCollection();

	void addRectangle(int, int, int, int);
	void addCircle(int, int, int );
	void addTriangle(int, int, int, int, int, int);

	double getPerOfFigureByIndex(size_t) const;
	double getAreaOfFigureByIndex(size_t) const;
	double getIfPointInShapeByIndex(size_t, int,int) const;
private:
	void resize();
	void addShape(Shape* shape);
	
	void free();
	void copyFrom(const ShapeCollection& other);

};