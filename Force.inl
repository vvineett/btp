#include <cmath>

#include "Force.h"

#define G 1
#define R 1

Vector collisionvanderwaalForces(const Particle&  a, const Particle& b);
Vector vanderwaalForce(const Particle& a, const Particle& b);

Force::Force() {

}

Force::~Force() {

}

vector<Vector> Force::vanderwaalForces(const vector<Particle>& particles) {
	vector<Vector> force(particles.size());

	int size = force.size();

	for(int i = 0; i<size-1; i++) {
		for(int j = i+1; j<size; j++) {
			Vector vf = vanderwaalForce(particles[i], particles[j]);
			force[i] = force[i] + vf;
			force[j] = force[j] - vf;
		}
	}

	return force;
}

Vector vanderwaalForce(const Particle& a, const Particle& b) {
	Vector f;

	if((a.getPosition()-b.getPosition()).length() <= a.getRadius() + b.getRadius()) {
		f = collisionvanderwaalForces(a,b);
	}
	else {
		f = ((G * a.getMass() * b.getMass())
				/pow((b.getPosition() - a.getPosition()).length(),3))* (b.getPosition() - a.getPosition());
	}

	return f;
}

Vector collisionvanderwaalForces(const Particle&  a, const Particle& b) {
	Vector f = (R * a.getMass() * b.getMass() * a.getRadius() * b.getRadius()
					/((a.getRadius() +b.getRadius())*pow((b.getPosition() - a.getPosition()).length(),3)))
					*(a.getPosition() - b.getPosition());
	return f;
}