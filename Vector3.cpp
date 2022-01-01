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

double Vector3::Dot(Vector3 x, Vector3 y) {
    return x._x * y._x + x._y * y._y + x._z * y._z;
}

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

double Vector3::length() {
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

Vector3 Vector3::unit() {
    Vector3 res = Vector3(_x, _y, _z);
    double length = res.length();
    return res / length;
}