#include "Compl.h"

void complex::setMod() {
	mod = sqrt(real * real + im * im);
}

double complex::getMod()const {

	return mod;

}

complex::complex() :real(0), im(0), mod(0) {}

complex::complex(double real, double im) {

	this->real = real;
	this->im = im;

	setMod();

}

complex& complex::operator=(const complex& rhs) {

	if (this != &rhs) {
		this->real = rhs.real;
		this->im = rhs.im;
		setMod();
	}

	return *this;
}

complex complex::getConjugate() const {

	complex temp(*this);
	temp.im *= -1;


	return temp;
}

complex& complex::operator+=(const complex& rhs) {

	this->real += rhs.real;
	this->im += rhs.im;

	setMod();

	return *this;
}

complex& complex::operator-=(const complex& rhs) {

	this->real -= rhs.real;
	this->im -= rhs.im;

	setMod();

	return *this;
}

complex& complex::operator*=(const complex& other)
{
	double oldReal = real;
	real = real * other.real - im * other.im;
	im = oldReal * other.im + im * other.real;

	setMod();

	return *this;
}

complex& complex::operator/=(const complex& other) {

	complex conjugatedOther = other.getConjugate();
	complex otherCopy(other);

	*this *= conjugatedOther;
	otherCopy *= conjugatedOther;

	if (otherCopy.real != 0) {
		real /= otherCopy.real;
		im /= otherCopy.im;
	}

	setMod();

	return *this;

}



std::ostream& operator<<(std::ostream& os, const complex& r) {

	os << r.real << "+" << r.im << "i";

	return os;

}

std::istream& operator>>(std::istream& ifs, complex& r) {
	ifs >> r.real >> r.im;

	r.setMod();

	return ifs;
}


complex operator+(const complex& lhs, const complex& rhs) {
	
	complex temp(lhs);
	temp += rhs;

	return temp;
}

complex operator-(const complex& lhs, const complex& rhs) {

	complex temp(lhs);
	temp -= rhs;

	return temp;
}

complex operator*(const complex& lhs, const complex& rhs) {

	complex temp(lhs);
	temp *= rhs;

	return temp;
}

complex operator/(const complex& lhs, const complex& rhs) {

	complex temp(lhs);
	temp /= rhs;
		
	return temp;
}

bool operator==(const complex& lhs, const complex& rhs) {
	return lhs.real == rhs.real && lhs.im == rhs.im;
}

bool operator!=(const complex& lhs, const complex& rhs) {
	return !(lhs == rhs);
}

complex operator*(const complex& obj, double scalar) {

	complex temp(obj);
	temp.real *= scalar;
	temp.im *= scalar;
	
	temp.mod = scalar*obj.getMod();

	return temp;
}

complex operator*(double scalar, const complex& obj) {
	return (obj * scalar);
}
