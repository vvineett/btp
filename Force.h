#ifndef _FORCE_H
#define _FORCE_H

#include <vector>
#include <map>

#include "Vector.h"
#include "Particle.h"

using namespace std;

class Force {
	// std::map<Particle*, Vector > forceMap;



	// Force(const vector<Particle>&);

public:
	Force();
	Force(const Force&);
	~Force();

	/*static factory method*/

	vector<Vector> vanderwaalForces(const vector<Particle>&);
};

#include "Force.inl"

#endif