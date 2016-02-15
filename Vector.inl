#include <iostream>
#include <cmath>

#include "Vector.h"

Vector :: Vector(double _i, double _j, double _k) {
	this->i = _i;
	this->j = _j;
	this->k = _k;
}

Vector :: Vector(const Vector& other) {
	this->i = other.i;
	this->j = other.j;
	this->k = other.k;
}

Vector :: ~Vector() {}


Vector operator* (const Vector& a, const Vector& b) {
	return Vector( a.j*b.k - a.k*b.j, a.k*b.i - a.i*b.k, a.i*b.j - a.j*b.i);
}

Vector operator+ (const Vector& a, const Vector& b) {
	return Vector( a.i+b.i, a.j+b.j, a.k+b.k);
}

Vector operator- (const Vector& a, const Vector& b) {
	return Vector( a.i-b.i, a.j-b.j, a.k-b.k);
}

Vector operator* (const double a, const Vector& v) {
	return Vector( a*v.i, a*v.j, a*v.k);
}

double operator| (const Vector& a, const Vector& b) {
	return (a.i*b.i + a.j*b.j + a.k*b.k);
}

double Vector :: length() {
	return sqrt((*this)|(*this));
}

/*io operations*/

std::ostream& operator<< (std::ostream& output, const Vector& v) {
	output << "( " << v.i << ", " << v.j << ", " << v.k << ")";
	return output;
}

std::istream& operator>> (std::istream& input, Vector& v) {
	input  >> v.i >> v.j >> v.k;

	return input;
}