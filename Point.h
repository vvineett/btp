#ifndef POINT_H
#define POINT_H

#include "Vector.h"

template <class T>
class Point {
    T x, y, z;

public:
    Point(T = 0, T = 0, T = 0);
    Point(const Point<T>&);

    ~Point();

    T xCoord() const {
        return x;
    }

    T yCoord() const {
        return y;
    }

    T zCoord() const {
        return z;
    }

    Point<T> movedBy(const Vector<T>&) const;

    double distanceFrom(const Point<T>&) const;

    template <class Y>
    friend bool operator< (const Point<Y>&, const Point<Y>&);

    template <class Y>
    friend bool operator> (const Point<Y>&, const Point<Y>&);

    template <class Y>
    friend bool operator== (const Point<Y>&, const Point<Y>&);

    template <class Y>
    friend Vector<Y> operator- (const Point<Y>&, const Point<Y>&);

    template <class Y>
    friend Point<Y> operator+ (const Point<Y>&, const Point<Y>&);

    template <class Y>
    friend Point<Y> operator* (const Y , const Point<Y>&);
    
    static Point<T> origin() {
        return Point<T>(0,0,0);
    }
};


#include <cmath>

template <class T>
Point<T>::Point(T _x, T _y, T _z) {
    this->x = _x;
    this->y = _y;
    this->z = _z;
}

template <class T>
Point<T>::Point(const Point<T> & other) {
    this->x = other.x;
    this->y = other.y;
    this->z = other.z;
}

template <class T>
Point<T>::~Point() {

}

template <class T>
Point<T> Point<T>::movedBy(const Vector<T>& v) const {
    return Point<T>(x+v.xComp(), y+v.yComp(), z+v.zComp());
}

template <class T>
double Point<T>::distanceFrom(const Point<T>& other) const{
    return sqrt(pow((this->x - other.x),2)+pow((this->y - other.y),2)+pow((this->z - other.z),2));
}

template <class T>
bool operator< (const Point<T>& a, const Point<T>& b) {
    const Point<T> origin(0,0,0);
    if(a.distanceFrom(origin) == b.distanceFrom(origin)) {
        if(a.x == b.x) {
            if(a.y==b.y) {
                return a.z < b.z;
            }
            return a.y < b.y;
        }
        return a.x < b.x;
    }

    return a.distanceFrom(origin) < b.distanceFrom(origin);
}

template <class T>
bool operator== (const Point<T>& a, const Point<T>& b) {
    if(a.x == b.x) {
        if(a.y==b.y) {
            return a.z == b.z;
        }
        return false;
    }

    return false;
}

template <class T>
bool operator> (const Point<T>& a, const Point<T>& b) {
    return !(a<b) && !(a==b);
}

template <class T>
Vector<T> operator- (const Point<T>& a, const Point<T>& b) {
    return Vector<T>(  a.x - b.x,
                    a.y - b.y,
                    a.z - b.z);
}

template <class T>
Point<T> operator+ (const Point<T>& a, const Point<T>& b) {
    return Point<T>(  a.x + b.x,
                    a.y + b.y,
                    a.z + b.z);
}

template <class T>
Point<T> operator* (const T a, const Point<T>& b) {
    return Point<T>(  b.x*a,
                    b.y*a,
                    b.z*a);
}

template class Point<int>;
template class Point<double>;

#endif /* POINT_H */

