#ifndef _BOX_H
#define _BOX_H

#include <iostream>

#include "Particle.h"
#include "Vector.h"
#include "Force.h"

class Box {
	Vector a, b, c; //edges of box
	vector<Particle> particles;
	vector<Vector> force;

	Box();
	Box(const Vector&, const Vector&, const Vector&);

	void applyBoundary();

	void applyPeriodicBoundary();

public:
	static Box boxWithEdges(const Vector&, const Vector&, const Vector&);

	void addParticles(int, int);

	void simulate(int nIter, double duration);
};

#include "Box.inl"

#endif