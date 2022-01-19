#include "common.h"
#include <cmath>

// constructor
Vector3d::Vector3d() : value_{0, 0, 0} {}
Vector3d::Vector3d(double x, double y, double z) : value_{x, y, z} {}

// set vec function
void Vector3d::set(double x, double y, double z)
{
    value_[0] = x;
    value_[1] = y;
    value_[2] = z;
}

// get vec function
double Vector3d::x() { return value_[0]; }
double Vector3d::y() { return value_[1]; }
double Vector3d::z() { return value_[2]; }

// operator
Vector3d Vector3d::operator-() { return Vector3d(-value_[0], -value_[1], -value_[2]); }

double Vector3d::operator[](int i) { return value_[i]; }

Vector3d& Vector3d::operator+=(Vector3d v) {
    value_[0] += v.x();
    value_[1] += v.y();
    value_[2] += v.z();
    return *this;
}

Vector3d& Vector3d::operator*=(double t) {
    value_[0] *= t;
    value_[1] *= t;
    value_[2] *= t;
    return *this;
}

Vector3d& Vector3d::operator/=(double t) {
    return *this *= 1/t;
}

// property
double Vector3d::Length() {
    return std::sqrt(LengthSquared());
}

double Vector3d::LengthSquared() {
    return value_[0] * value_[0] + value_[1] * value_[1] + value_[2] * value_[2];
}

Vector3d Vector3d::Random() {
    return Vector3d(RandomDouble(), RandomDouble(), RandomDouble());
}

Vector3d Vector3d::Random(double min, double max) {
    return Vector3d(RandomDouble(min, max), RandomDouble(min, max), RandomDouble(min, max));
}

Vector3d Vector3d::RandomInUnitSphere() {
    while (true) {
        auto p = Vector3d::Random(-1, 1);
        if (p.LengthSquared() >= 1) continue;
        return p;
    }
}

Vector3d Vector3d::RandomUnitVector() {
    // on sphere S
    return UnitVector(RandomInUnitSphere());
}

Vector3d Vector3d::RandomInHemisphere(Vector3d normal) {
    Vector3d in_unit_sphere = RandomInUnitSphere();
    if (Dot(in_unit_sphere, normal) > 0.0) return in_unit_sphere;
    else {return -in_unit_sphere;}
}

Vector3d Vector3d::RandomUnitDisk() {
    while (true) {
        auto p = Vector3d(RandomDouble(-1,1), RandomDouble(-1,1), 0);
        if (p.LengthSquared() >= 1) continue;
        return p;
    }
}

bool Vector3d::NearZero() {
    // Return true if the vector is close to zero in all dimensions.
    const auto s = 1e-8;
    return (fabs(value_[0]) < s) && (fabs(value_[1]) < s) && (fabs(value_[2]) < s);
}

Vector3d Refract(Vector3d uv, Vector3d n, double etai_over_etat) {
    auto cos_theta = fmin(Dot(-uv, n), 1.0);
    Vector3d r_out_perp =  etai_over_etat * (uv + cos_theta*n);
    Vector3d r_out_parallel = -sqrt(fabs(1.0 - r_out_perp.LengthSquared())) * n;
    return r_out_perp + r_out_parallel;
}

void write_color(std::ostream &out, Vector3d pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * Clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * Clamp(b, 0.0, 0.999)) << '\n';
}
