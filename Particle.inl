#include "Particle.h"

Particle :: Particle(double _mass, double _charge, double _radius, Vector _position, Vector _velocity, Vector _acc) {
	this->mass = _mass;
	this->charge = _charge;
	this->radius = _radius;
	this->position = _position;
	this->velocity = _velocity;
	this->acc = _acc;
	this->halfVel = Vector();
}

Particle :: Particle(const Particle& other) {
	this->mass = other.mass;
	this->charge = other.charge;
	this->radius = other.radius;
	this->position = other.position;
	this->velocity = other.velocity;
	this->acc = other.acc;
	this->halfVel = other.halfVel;
}

Particle :: ~Particle() {

}

/* Helper functions for velocity verlet */
void Particle :: updateAcceleration(const Vector& force) {
	this->acc = (1.0/mass)*force;
}

void Particle :: updateHalfVelocity(double timeInterval) {
	this->halfVel = this->velocity + (timeInterval/2.0)*this->acc;
}

void Particle :: updatePosition(double timeInterval) {
	this->position = this->position + timeInterval*this->halfVel;
}

void Particle::updateVelocity(double timeInterval) {
	this->velocity = this->halfVel + (timeInterval/2.0)*this->acc;
}
/********** Helpers end *********/

/** Velocity Verlet Update **/
void Particle::updateByVelocityVerlet(const Vector& force, double timeInterval) {
	updateHalfVelocity(timeInterval);
	updatePosition(timeInterval);
	updateAcceleration(force);
	updateVelocity(timeInterval);
}

/*Boundary Conditions*/
double sign(double a) {
	if(a>0) return 1;

	if(a<0) return -1;

	return 0;
}


void Particle::checkBoundaryConditions(const Vector& a, const Vector& b, const Vector& c) {

	if( (a*b) != Vector() && (b*c) != 0 && (c*a) != 0) {
		Vector nbc = sign(a|(b*c))*(1/(b*c).length())*(b*c);
		Vector nca = sign(b|(c*a))*(1/(c*a).length())*(c*a);
		Vector nab = sign(c|(a*b))*(1/(a*b).length())*(a*b);

		if((nbc|a) < (nbc|position)) {
			position = position - 2*((nbc|Vector(position)) - (nbc|a))*nbc;
			velocity = velocity - 2*((nbc|Vector(velocity))*nbc);
		}
		else if((nbc|position) < 0) {
			position = position - 2*(nbc|Vector(position))*nbc;
			velocity = velocity - 2*((nbc|Vector(velocity))*nbc);
		}

		if((nca|b) < (nca|position)) {
			position = position - 2*((nca|position) - (nca|b))*nca;
			velocity = velocity - 2*((nca|Vector(velocity))*nca); 
		}
		else if((nca|position) < 0) {
			position = position - 2*(nca|position)*nca;
			velocity = velocity - 2*((nca|Vector(velocity))*nca); 
		}

		if((nab|c) < (nab|position)) {
			position = position - 2*((nab|position) - (nab|c))*nab;
			velocity = velocity - 2*((nab|Vector(velocity))*nab); 
		}
		else if((nab|position) < 0) {
			position = position - 2*(nab|position)*nab;
			velocity = velocity - 2*((nab|Vector(velocity))*nab); 

		}
	}
	else {
		if( a.length() < position.length() && (position|a) > 0) {
			position = position - 2*(position - a);
			velocity = -1*velocity;
		}
		else if((position|a) < 0) {
			position = -1*position;
			velocity = -1*velocity; 
		}
	}

}

void Particle::applyPeriodicBoundaryConditions(const Vector& a, const Vector& b, const Vector& c) {
	
}
