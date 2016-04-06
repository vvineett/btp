#ifndef FORCE_H
#define FORCE_H

#include <vector>
#include <map>

#include "Vector.h"
#include "Particle.h"

using namespace std;

class Force {
    // std::map<Particle*, Vector<double> > forceMap;



    // Force(const vector<Particle>&);

public:
    Force();
    Force(const Force&);
    ~Force();

    /*static factory method*/

    vector<Vector<double>> vanderwaalForces(const vector<Particle>&);
};

#endif /* FORCE_H */

