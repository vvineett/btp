#ifndef _VECTOR_H
#define _VECTOR_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>


class Vector {
	double i,j,k;

public:
	Vector(double = 0, double = 0, double = 0);
	Vector(const Vector&);

	~Vector();

	double length() const;

	friend Vector operator* (const Vector&, const Vector&);  //Vector Product
	friend Vector operator- (const Vector&, const Vector&);  //substraction
	friend Vector operator+ (const Vector&, const Vector&);  //vector addition
	friend Vector operator* (const double, const Vector&);   //scalar multiplication
	friend double operator| (const Vector&, const Vector&);  //scalar product of vectors

	friend bool operator== (const Vector&, const Vector&);
	friend bool operator!= (const Vector&, const Vector&);

	/* basic io operations*/
	friend std::ostream& operator<< (std::ostream&, const Vector&);
	friend std::istream& operator>> (std::istream&, Vector&);

	std::string print() {
		char printer[200];
		sprintf(printer, "%lf %lf %lf", i, j, k);

		return std::string(printer);
	}

};

#include "Vector.inl"

#endif