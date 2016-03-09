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

	/*helpers for velocity verlet*/
	void updateAcceleration(const Vector&);
	void updateVelocity(double = 1);
	void updateHalfVelocity(double = 1);
	void updatePosition(double = 1);

public:

	Particle(double = 0, double = 0, double = 0, Vector = Vector(), Vector = Vector(), Vector = Vector());
	Particle(const Particle&);
	~Particle();

	

	/* velocity verlet*/
	void updateByVelocityVerlet(const Vector&, double);


	/* Particle in box*/
	void checkBoundaryCondtions(const Vector&, const Vector&, const Vector&);

	/*particle in periodic boundary box */
	void applyPeriedicBoundaryConditions(const Vector&, const Vector&, const Vector&);

	/* position, velocity, acc printers*/
	void printPosVelAcc() {
		std::cout << position << "\t" << velocity << "\t" << acc << "\n";
	}
};

/* function definitions in this file*/
#include "Particle.inl"

#endif