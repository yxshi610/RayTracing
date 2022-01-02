#include "main.h"
#include <cmath>

// vec constructor
Vector3::Vector3(double x, double y, double z)
{
    set(x, y, z);
}

// set vec function
void Vector3::set(double a, double b, double c)
{
    _x = a;
    _y = b;
    _z = c;
}

// get vec function
double Vector3::x() { return _x; }
double Vector3::y() { return _y; }
double Vector3::z() { return _z; }

Vector3 Vector3::random() {
    return Vector3(random_double(), random_double(), random_double());
}

Vector3 Vector3::random(double min, double max) {
    return Vector3(random_double(min, max), random_double(min, max), random_double(min, max));
}

Vector3 Vector3::random_in_unit_sphere() {
    while (true) {
        auto p = Vector3::random(-1, 1);
        if (p.length() * p.length() >= 1) continue;
        return p;
    }
}

Vector3 Vector3::random_unit_sphere() {
    // on sphere S
    return Vector3::random_in_unit_sphere().unit();
}

bool Vector3::near_zero() {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(_x) < s) && (fabs(_y) < s) && (fabs(_z) < s);
}


double Vector3::length() {
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

Vector3 Vector3::unit() {
    Vector3 res = Vector3(_x, _y, _z);
    double length = res.length();
    return res / length;
}