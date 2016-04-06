#ifndef VECTOR_H
#define VECTOR_H

#include <cmath>
#include <iosfwd>

template <class T>
class Vector {
    T i, j, k;

public:
    Vector(T = 0, T = 0, T = 0);
    Vector(const Vector<T>&);
    ~Vector();

    T xComp() const {
        return i;
    }

    T yComp() const {
        return j;
    }

    T zComp() const {
        return k;
    }

    double length() const;

    template <class Y>
    friend Vector<Y> operator*(const Vector<Y>&, const Vector<Y>&); //Vector Product

    template <class Y>
    friend Vector<Y> operator-(const Vector<Y>&, const Vector<Y>&); //substraction

    template <class Y>
    friend Vector<Y> operator+(const Vector<Y>&, const Vector<Y>&); //vector addition

    template <class Y>
    friend Vector<Y> operator*(const Y, const Vector<Y>&); //scalar multiplication

    template <class Y>
    friend Y operator|(const Vector<Y>&, const Vector<Y>&); //scalar product of vectors

    template <class Y>
    friend bool operator==(const Vector<Y>&, const Vector<Y>&);
    template <class Y>
    friend bool operator!=(const Vector<Y>&, const Vector<Y>&);



    /* basic i/o operations*/
    /*  friend std::ostream& operator<< (std::ostream&, const Vector&);
        friend std::istream& operator>> (std::istream&, Vector&); */
};

template <class T>
Vector<T>::Vector(T _i, T _j, T _k) {
    this->i = _i;
    this->j = _j;
    this->k = _k;
}

template <class T>
Vector<T>::Vector(const Vector<T>& other) {
    this->i = other.i;
    this->j = other.j;
    this->k = other.k;
}

template <class T>
Vector<T>::~Vector() {
}

template <class T>
Vector<T> operator*(const Vector<T>& a, const Vector<T>& b) {
    return Vector<T>(a.j * b.k - a.k * b.j, a.k * b.i - a.i * b.k, a.i * b.j - a.j * b.i);
}

template <class T>
Vector<T> operator+(const Vector<T>& a, const Vector<T>& b) {
    return Vector<T>(a.i + b.i, a.j + b.j, a.k + b.k);
}

template <class T>
Vector<T> operator-(const Vector<T>& a, const Vector<T>& b) {
    return Vector<T>(a.i - b.i, a.j - b.j, a.k - b.k);
}

template <class T>
Vector<T> operator*(const T a, const Vector<T>& v) {
    return Vector<T>(a * v.i, a * v.j, a * v.k);
}

template <class T>
T operator|(const Vector<T>& a, const Vector<T>& b) {
    return (a.i * b.i + a.j * b.j + a.k * b.k);
}

template <class T>
bool operator==(const Vector<T>& a, const Vector<T>& b) {
    return ((a.i == b.i) && (a.j == b.j) && (a.k == b.k));
}

template <class T>
bool operator!=(const Vector<T>& a, const Vector<T>& b) {
    return !(a == b);
}

template <class T>
double Vector<T>::length() const {
    return sqrt((*this) | (*this));
}

/*io operations*/
/*
template <class T>
std::ostream& operator<< (std::ostream& output, const Vector<T>& v) {
    output << string("( ") << v.i << string(", ") << v.j << string(", ") << v.k << string(")");
    return output;
}

template <class T>
std::istream& operator>> (std::istream& input, Vector<T>& v) {
    input  >> v.i >> v.j >> v.k;

    return input;
} */

template class Vector<int>;
template class Vector<double>;


#endif /* VECTOR_H */

