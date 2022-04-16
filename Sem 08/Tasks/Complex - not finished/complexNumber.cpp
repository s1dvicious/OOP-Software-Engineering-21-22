#include "complexNumber.h"

double complex::getMod() const {
	return sqrt(real * real + im * im);
}

complex::complex(): real(0), im(0){}

complex::complex(double x, double y): real(x), im(y){}

complex& complex::operator+=(const complex& rhs) {

	real += rhs.real;
	im += rhs.im;

	return *this;
}

complex operator+(const complex& lhs, const complex& rhs) {

	complex temp(lhs);
	temp += rhs;

	return temp;
}

complex& complex::operator*=(const complex& rhs) {

	double oldReal = real;

	real = real * rhs.real - im * rhs.im;
	im = oldReal * rhs.im + im * rhs.real;

	return *this;
}

complex operator*(const complex& lhs, const complex& rhs) {

	complex temp(lhs);
	temp *= rhs;

	return temp;
}


void complex::print()const{

	std::cout << real << "+i" << im;
}

