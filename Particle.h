#ifndef _PARTICLE_H
#define _PARTICLE_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>

#include "Vector.h"


class Particle {
	std::string symbol;
	double mass;		/* micrograms*/
	double charge;		/* Coulombs */
	double radius; 		/* in Angstorm*/
	Vector position; 	/* Angstorm*/
	Vector velocity;
	Vector halfVel;
	Vector acc;

	/*helpers for velocity verlet*/
	void updateAcceleration(const Vector&);
	void updateVelocity(double = 1);
	void updateHalfVelocity(double = 1);
	void updatePosition(double = 1);

public:

	Particle(std::string = std::string("X"), double = 0, double = 0, double = 0, Vector = Vector(), Vector = Vector(), Vector = Vector());
	Particle(const Particle&);
	~Particle();

	

	/* velocity verlet*/
	void updateByVelocityVerlet(const Vector&, double);


	/* Particle in box*/
	void applyBoundaryConditions(const Vector&, const Vector&, const Vector&);

	/*particle in periodic boundary box */
	void applyPeriodicBoundaryConditions(const Vector&, const Vector&, const Vector&);

	/* position, velocity, acc printers*/
	void printPosVelAcc() {
		std::cout << position << "\t" << velocity << "\t" << acc << "\n";
	}

	/*traj format*/
	std::string toXYZ() {
		char printer[200];
		sprintf(printer, "%s %s", symbol.c_str(), position.print().c_str());

		return std::string(printer);
	}

	/*getters*/

	Vector getPosition() const {
		return Vector(position);
	}

	double getRadius() const {
		return radius;
	}

	double getMass() const {
		return mass;
	}
};

/* function definitions in this file*/
#include "Particle.inl"

#endif