#include <cstdlib>

#include "Box.h"

string printer(int n) {
    char printer[20];
    sprintf(printer, "%d", n);

    return std::string(printer);
}

Box::Box() {

}

Box::Box(const Vector<double>& a, const Vector<double>& b, const Vector<double>& c) {
    this->a = a;
    this->b = b;
    this->c = c;
}

Box Box::boxWithEdges(const Vector<double>& a, const Vector<double>& b, const Vector<double>& c) {
    return Box(a, b, c);
}

void Box::addParticles(int n, int seed) {
    srand(seed);

    for (int i = 0; i < n; i++) {
        Point<double> pos = Point<double>::origin().movedBy(((double(rand() % 99 + 1)/100.0) * a)
                                        +((double(rand() % 99 + 1) / 100.0) * b)
                                        +((double(rand() % 99 + 1) / 100.0) * c));
        Vector<double> vel;
        Vector<double> a;

        Particle p(std::string("X"), 1, 0, 0.5, pos, vel, a);

        particles.push_back(p);
    }

    return;
}

void Box::addParticles(const vector<Particle>& parts) {
    int n = parts.size();
    for (int i = 0; i < n; i++) {
        particles.push_back(parts[i]);
    }

    return;
}

void Box::simulate(int nIter, double duration) {
    // std::cout<<"Simuation starts: nIter = " << nIter << " , each iteration duration = " << duration << std::endl;
    for (int i = 0; i < nIter; i++) {
        this->xyz += printer(particles.size()) + string("\n");
        // std::cout<< "i= " << i+1 << std::endl;
        force = Force().vanderwaalForces(particles);
        for (int j = 0; j < particles.size(); j++) {
            particles[j].updateByVelocityVerlet(force[j], duration);
        }

        applyBoundary();

        for (int j = 0; j < particles.size(); j++) {
            this->xyz += particles[j].toXYZ() + string("\n");
        }


        // std::cout<< std::endl;

    }

}

void Box::applyBoundary() {
    for (int j = 0; j < particles.size(); j++) {
        particles[j].applyBoundaryConditions(a, b, c);
    }
}

void Box::applyPeriodicBoundary() {
    for (int j = 0; j < particles.size(); j++) {
        particles[j].applyPeriodicBoundaryConditions(a, b, c);
    }
}
