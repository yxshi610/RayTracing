#include "Vector3.h"
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

double Vector3::length() {
    return std::sqrt(_x * _x + _y * _y + _z * _z);
}

Vector3 Vector3::unit() {
    Vector3 res = Vector3(_x, _y, _z);
    double length = res.length();
    return res / length;
}


void write_color(std::ostream &out, Vector3 pixel_color) {
    out << static_cast<int>(255.999 * pixel_color.x()) << ' '
        << static_cast<int>(255.999 * pixel_color.y()) << ' '
        << static_cast<int>(255.999 * pixel_color.z()) << '\n';
}