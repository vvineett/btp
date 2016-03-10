#include <iostream>
#include <vector>

#include "Vector.h"
#include "Particle.h"
#include "Box.h"
#include "Force.h"

using namespace std;


int main(int argc, char** argv) {
	int num = 3;

	Vector a(10,0,0), b(0,0,0), c(0,0,0);

	Box box = Box().boxWithEdges(a,b,c);

	box.addParticles(num, 2*num+1);

	box.simulate(100, 0.1);

	// Particle p(1,0,0.000001, a, b, c);
	// p.printPosVelAcc();

	// c = a;
	// cout<< c;

	return 0;
}