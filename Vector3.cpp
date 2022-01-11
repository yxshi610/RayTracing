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
    _e[0] = a;
    _y = b;
    _e[1] = b;
    _z = c;
    _e[2] = c;
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
    return std::sqrt(length_squared());
}

double Vector3::length_squared() {
    return _x * _x + _y * _y + _z * _z;
}

Vector3 Vector3::unit() {
    Vector3 res = Vector3(_x, _y, _z);
    double length = res.length();
    return res / length;
}

Vector3 refract(Vector3 uv, Vector3 n, double etai_over_etat) {
    auto cos_theta = fmin(dot(-uv, n), 1.0);
    Vector3 r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Vector3 r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.length_squared())) * n;
    return r_out_perp + r_out_parallel;
}