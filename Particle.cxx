#include "Particle.h"

Particle::Particle(std::string _symbol,
        double _mass,
        double _charge,
        double _radius,
        Point<double> _position,
        Vector<double> _velocity,
        Vector<double> _acc) {

    this->symbol = _symbol;
    this->mass = _mass;
    this->charge = _charge;
    this->radius = _radius;
    this->position = _position;
    this->velocity = _velocity;
    this->acc = _acc;
    this->halfVel = Vector<double>();
}

Particle::Particle(const Particle& other) {
    this->symbol = other.symbol;
    this->mass = other.mass;
    this->charge = other.charge;
    this->radius = other.radius;
    this->position = other.position;
    this->velocity = other.velocity;
    this->acc = other.acc;
    this->halfVel = other.halfVel;
}

Particle::~Particle() {

}

/* Helper functions for velocity verlet */
void Particle::updateAcceleration(const Vector<double>& force) {
    this->acc = (1.0 / mass) * force;
}

void Particle::updateHalfVelocity(double timeInterval) {
    this->halfVel = this->velocity + (timeInterval / 2.0) * this->acc;
}

void Particle::updatePosition(double timeInterval) {
    this->position = this->position.movedBy(timeInterval * this->halfVel);
}

void Particle::updateVelocity(double timeInterval) {
    this->velocity = this->halfVel + (timeInterval / 2.0) * this->acc;
}
/********** Helpers end *********/

/** Velocity Verlet Update **/
void Particle::updateByVelocityVerlet(const Vector<double>& force, double timeInterval) {
    updateHalfVelocity(timeInterval);
    updatePosition(timeInterval);
    updateAcceleration(force);
    updateVelocity(timeInterval);
}

/*Boundary Conditions*/
double sign(double a) {
    if (a > 0) return 1.0;

    if (a < 0) return -1.0;

    return 0;
}

void Particle::applyBoundaryConditions(const Vector<double>& a, const Vector<double>& b, const Vector<double>& c) {

    Vector<double> positionVector = position - Point<double>::origin();
    
    /* check if any of the two vectors are parallel, Vector<double>() == Vector<double>(0,0,0)*/
    if ((a * b) != Vector<double>() && (b * c) != Vector<double>() && (c * a) != Vector<double>()) {
        Vector<double> nbc = sign(a | (b * c))*(1.0 / (b * c).length())*(b * c); /* normal to plane containing b and c,
															  	such that it has positive component towards a*/

        Vector<double> nca = sign(b | (c * a))*(1.0 / (c * a).length())*(c * a); /*normal to plane containing a and c*/
        Vector<double> nab = sign(c | (a * b))*(1.0 / (a * b).length())*(a * b); /*normal to plane containing b and a*/

        /* check if particle is farther than a's component in direction parallel to nbc*/
        
        if ((nbc | a) < ((nbc | positionVector))) {
            position = position.movedBy(-2.0 * ((nbc | positionVector) - (nbc | a)) * nbc);
            velocity = velocity - 2.0 * ((nbc | Vector<double>(velocity)) * nbc);
        } else if (((nbc | positionVector)) < 0) {
            position = position.movedBy(- 2.0 * (nbc | positionVector) * nbc);
            velocity = velocity - 2.0 * ((nbc | Vector<double>(velocity)) * nbc);
        }

        if ((nca | b) < (nca | positionVector)) {
            position = position.movedBy(-2.0 * ((nca | positionVector) - (nca | b)) * nca);
            velocity = velocity - 2.0 * ((nca | Vector<double>(velocity)) * nca);
        } else if ((nca | positionVector) < 0) {
            position = position.movedBy( -2.0 * (nca | positionVector) * nca);
            velocity = velocity - 2.0 * ((nca | Vector<double>(velocity)) * nca);
        }

        if ((nab | c) < (nab | positionVector)) {
            position = position.movedBy( -2.0 * ((nab | positionVector) - (nab | c)) * nab);
            velocity = velocity - 2.0 * ((nab | Vector<double>(velocity)) * nab);
        } else if ((nab | positionVector) < 0) {
            position = position.movedBy( -2.0 * (nab | positionVector) * nab);
            velocity = velocity - 2.0 * ((nab | Vector<double>(velocity)) * nab);

        }
    } else {
        if (a.length() < positionVector.length() && (positionVector | a) > 0) {
            position = position.movedBy( -2.0 * (positionVector - a));
            velocity = -1.0 * velocity;
        } else if ((positionVector | a) < 0) {
            position = -1.0 * position;
            velocity = -1.0 * velocity;
        }
    }

}

void Particle::applyPeriodicBoundaryConditions(const Vector<double>& a, const Vector<double>& b, const Vector<double>& c) {

    Vector<double> positionVector = position - Point<double>::origin();
    
    /* check if any of the two vectors are parallel, Vector<double>() == Vector<double>(0,0,0)*/
    if ((a * b) != Vector<double>() && (b * c) != Vector<double>() && (c * a) != Vector<double>()) {
        Vector<double> nbc = sign(a | (b * c))*(1.0 / (b * c).length())*(b * c); /* normal to plane containing b and c,
															  	such that it has positive component towards a*/

        Vector<double> nca = sign(b | (c * a))*(1.0 / (c * a).length())*(c * a); /*normal to plane containing a and c*/
        Vector<double> nab = sign(c | (a * b))*(1.0 / (a * b).length())*(a * b); /*normal to plane containing b and a*/

        /* check if particle is farther than a's component in direction parallel to nbc*/
        if ((nbc | a) < ((nbc | positionVector))) {
            position = position.movedBy(-1.0*a); /* particle enters in opposite side of box*/
        }            /* check if particle is out of box in opposite direction as a parallel to nbc*/
        else if (((nbc | positionVector)) < 0) {
            position = position.movedBy(a);
        }

        if ((nca | b) < (nca | positionVector)) {
            position = position.movedBy(-1.0*b);
        } else if ((nca | positionVector) < 0) {
            position = position.movedBy(b);
        }

        if ((nab | c) < (nab | positionVector)) {
            position = position.movedBy(-1.0*c);
        } else if ((nab | positionVector) < 0) {
            position = position.movedBy(c);
        }
    }
}

