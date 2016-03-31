#include <iostream>
#include <vector>

#include "Vector.h"
#include "Particle.h"
#include "Box.h"
#include "Force.h"
#include "SimBoxBuilder.h"

using namespace std;


int main(int argc, char** argv) {

	// if(tokens[0].find(string("nIter")) != string::npos) {
	// 	nIter = stoi(tokens[1]);
	// }
	// else if(tokens[0].find(string("duration")) != string::npos) {
	// 	duration = stod(tokens[1]);
	// }

	Box box = SimBoxBuilder().fromParamFile(string("param.in"), true);

	box.simulate(1000, 0.1);

	// Particle p(1,0,0.000001, a, b, c);
	// p.printPosVelAcc();

	// c = a;
	// cout<< c;

	return 0;
}