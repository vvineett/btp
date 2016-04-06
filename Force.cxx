#include <cmath>

#include "Force.h"

#define G 1
#define R 1

Vector<double> collisionvanderwaalForces(const Particle& a, const Particle& b);
Vector<double> vanderwaalForce(const Particle& a, const Particle& b);

Force::Force() {

}

Force::~Force() {

}

vector<Vector<double>> Force::vanderwaalForces(const vector<Particle>& particles) {
    vector<Vector<double>> force(particles.size());

    int size = force.size();

    for (int i = 0; i < size - 1; i++) {
        for (int j = i + 1; j < size; j++) {
            Vector<double> vf = vanderwaalForce(particles[i], particles[j]);
            force[i] = force[i] + vf;
            force[j] = force[j] - vf;
        }
    }

    return force;
}

Vector<double> vanderwaalForce(const Particle& a, const Particle& b) {
    Vector<double> f;

    if ((a.getPosition() - b.getPosition()).length() <= a.getRadius() + b.getRadius()) {
        f = collisionvanderwaalForces(a, b);
    } else {
        f = ((G * a.getMass() * b.getMass())
                / pow((b.getPosition() - a.getPosition()).length(), 3))* (b.getPosition() - a.getPosition());
    }

    return f;
}

Vector<double> collisionvanderwaalForces(const Particle& a, const Particle& b) {
    Vector<double> f = (R * a.getMass() * b.getMass() * a.getRadius() * b.getRadius()
            / ((a.getRadius() + b.getRadius()) * pow((b.getPosition() - a.getPosition()).length(), 3)))
            *(a.getPosition() - b.getPosition());
    return f;
}