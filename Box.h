#ifndef BOX_H
#define BOX_H

#include <iostream>
#include <string>

#include "Particle.h"
#include "Vector.h"
#include "Force.h"

class Box {
    Vector<double> a, b, c; //edges of box
    vector<Particle> particles;
    vector<Vector<double>> force;
    
    string xyz;
    
    Box(const Vector<double>&, const Vector<double>&, const Vector<double>&);

    void applyBoundary();

    void applyPeriodicBoundary();

public:
    Box();

    Box boxWithEdges(const Vector<double>&, const Vector<double>&, const Vector<double>&);

    void addParticles(int, int);

    void addParticles(const vector<Particle>&);

    void simulate(int nIter, double duration);
    
    string toXYZ() const {
        return this->xyz;
    }
};

#endif /* BOX_H */
