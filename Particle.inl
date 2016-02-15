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

void Particle :: updateVelocity(double timeInterval) {
	this->velocity = this->halfVel + (timeInterval/2.0)*this->acc;
}
/********** Helpers end *********/

/** Velocity Verlet Update **/
void Particle :: updateByVelocityVerlet(const Vector& force, double timeInterval) {
	updateHalfVelocity(timeInterval);
	updatePosition(timeInterval);
	updateAcceleration(force);
	updateVelocity(timeInterval);
}