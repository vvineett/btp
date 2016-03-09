#include <cstdlib>

#include "Box.h"


Box::Box() {

}

Box::Box(const Vector& a, const Vector& b, const Vector& c) {
	this->a = a;
	this->b = b;
	this->c = c;
}

Box Box::boxWithEdges(const Vector& a, const Vector& b, const Vector& c) {
	return Box(a,b,c);
}

void Box::addParticles(int n, int seed) {
	srand(seed);

	for(int i = 0; i<n; i++) {
		Vector pos = (((double)(rand()%99 + 1)/100.0)*a) + (((double)(rand()%99 + 1)/100.0)*b) +(((double)(rand()%99 + 1)/100.0)*c);
		Vector vel;
		Vector a;

		Particle p(1,0,0.000001, pos, vel, a);

		particles.push_back(p);
	}

	return;
}

void Box::simulate(int nIter, double duration) {
	std::cout<<"Simuation starts: nIter = " << nIter << " , each iteration duration = " << duration << std::endl;
	for(int i=0; i<nIter; i++) {
		std::cout<< "i= " << i+1 << std::endl;
		force = Force().vanderwaalForces(particles);
		for(int j=0; j< particles.size(); j++) {
			particles[j].updateByVelocityVerlet(force[j], duration);
		}

		applyBoundary();

		for(int j = 0; j<particles.size(); j++) {
			particles[j].printPosVelAcc();
		}


		std::cout<< "---------------------------------------------------------------------------------------" << std::endl;

	}

}

void Box::applyBoundary() {
	for(int j = 0; j< particles.size(); j++) {
		particles[j].checkBoundaryConditions(a, b, c);
	}
}