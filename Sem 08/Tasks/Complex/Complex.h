#ifndef COMPLEX_H
#define COMPLEX_H
#include<iostream>
#include<fstream>

class complex {
	double real;
	double im;

	double mod;

	void setMod();
public:

	double getMod()const;

	//Normally one would define selectors (get-ers) but for the sake
	//of the example we'll restrain ourselves from that
	friend class complexSeq;
    
	//Constructors
	complex();
	complex(double, double);

	complex& operator=(const complex&);

	complex getConjugate()const; //returns the complex conjugate of this!

	//Compound assignment operators 
	complex& operator+=(const complex&);
	complex& operator-=(const complex&);
	complex& operator*=(const complex&);
	complex& operator/=(const complex&);

	//multiplication with a scalar
	//complex& operator*=(double);

	//stdin/stdout streams (file streams are automatically overriden!)
	friend std::ostream& operator<<(std::ostream&, const complex&);
	friend std::istream& operator>>(std::istream&, complex&);

	//relational operators
	friend bool operator==(const complex&,const complex&);
	friend bool operator!=(const complex&, const complex&);

	//multiplication with a scalar
	friend complex operator*(const complex&, double);
	friend complex operator*(double, const complex&);
};

//assignment operators
complex operator+(const complex&, const complex&);
complex operator-(const complex&, const complex&);
complex operator*(const complex&, const complex&);
complex operator/(const complex&, const complex&);

#endif
