#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <iostream>

#include "Vector.h"


class Particle {
	double mass;
	double charge;
	double radius;
	Vector position;
	Vector velocity;
	Vector halfVel;
	Vector acc;

public:

	Particle(double = 0, double = 0, double = 0, Vector = Vector(), Vector = Vector(), Vector = Vector());
	Particle(const Particle&);
	~Particle();

	/*helpers for velocity verlet*/
	void updateAcceleration(const Vector&);
	void updateVelocity(double = 1);
	void updateHalfVelocity(double = 1);
	void updatePosition(double = 1);

	/* velocity verlet*/
	void updateByVelocityVerlet(const Vector&, double);

	/* position, velocity, acc printers*/
	void printPosVelAcc() {
		std::cout << position << "\t" << velocity << "\t" << acc << "\n";
	}
};

/* function definitions in this file*/
#include "Particle.inl"

#endif