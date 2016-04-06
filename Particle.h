#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <string>
#include <cstdio>
#include <cstring>

#include "Vector.h"

class Particle {
    std::string symbol;
    double mass; /* micrograms*/
    double charge; /* Coulombs */
    double radius; /* in Angstorm*/
    Vector<double> position; /* Angstorm*/
    Vector<double> velocity;
    Vector<double> halfVel;
    Vector<double> acc;

    /*helpers for velocity verlet*/
    void updateAcceleration(const Vector<double>&);
    void updateVelocity(double = 1);
    void updateHalfVelocity(double = 1);
    void updatePosition(double = 1);

public:

    Particle(std::string = std::string("X"), double = 0, double = 0, double = 0, Vector<double> = Vector<double>(), Vector<double> = Vector<double>(), Vector<double> = Vector<double>());
    Particle(const Particle&);
    ~Particle();



    /* velocity verlet*/
    void updateByVelocityVerlet(const Vector<double>&, double);


    /* Particle in box*/
    void applyBoundaryConditions(const Vector<double>&, const Vector<double>&, const Vector<double>&);

    /*particle in periodic boundary box */
    void applyPeriodicBoundaryConditions(const Vector<double>&, const Vector<double>&, const Vector<double>&);

//    /* position, velocity, acc printers*/
//    void printPosVelAcc() {
//        std::cout << position << "\t" << velocity << "\t" << acc << "\n";
//    }

    /*traj format*/
    std::string toXYZ() {
        char printer[200];
        sprintf(printer, "%s %lf %lf %lf", symbol.c_str(), position.xComp(), position.yComp(), position.zComp());

        return std::string(printer);
    }

    /*getters*/

    Vector<double> getPosition() const {
        return Vector<double>(position);
    }

    double getRadius() const {
        return radius;
    }

    double getMass() const {
        return mass;
    }
};

#endif /* PARTICLE_H */

