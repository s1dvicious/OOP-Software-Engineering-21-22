#pragma once
#include<iostream>
class complex {
	double real;
	double im;
	
	double getMod()const;
public:

	complex();
	complex(double, double);

	complex& operator+=(const complex&);
	complex& operator*=(const complex&);

	void print()const;
};


complex operator+(const complex&, const complex&);
complex operator*(const complex&, const complex&);

