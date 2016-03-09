#include "Force.h"

Force::Force() {

}

static vector<Vector> Force::vanderwaalForces(const vector<Particle>& particles) {
	vector<Vector> force(particles.size());

	int size = force.size();

	for(int i = 0; i<size-1; i++) {
		for(int j = i+1; j<size; j++) {
			Vector vf = vanderwaalForce(particles[i], particles[j])
			force[i] = force[i] + v;
			force[j] = force[j] - v;
		}
	}

	return force;
}

friend Vector vanderwaalForce(const Particle& a, const Particle& b) {
	Vector f;

	if((a.position-b.position).length() < a.radius + b.radius) {
		f = collisionvanderwaalForces(a,b);
	}
	else {
		f = ((G * a.m * b.m)/pow((b.position - a.position).length()),3))* (b.position - a.position);
	}
}

friend Vector collisionvanderwaalForces(const Particle&  a, const Particle& b) {
	Vector f = (((G * a.m * b.m*)/pow((b.position - a.position).length()),3))* (a.position - b.position))
}