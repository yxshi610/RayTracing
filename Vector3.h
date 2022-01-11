#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

class Vector3
{
private:
    double _x;
    double _y;
    double _z;
    double _e[3];

public:
    Vector3(double x = 0, double y = 0, double z = 0);
    void set(double x, double y, double z);
    double x();
    double y();
    double z();
    double operator[](int i) const { return _e[i]; }
    double& operator[](int i) { return _e[i]; }

    static Vector3 random();
    static Vector3 random(double min, double max);

    static Vector3 random_in_unit_sphere();
    static Vector3 random_unit_sphere();
    
    
    bool near_zero();
    double length();
    double length_squared();

    Vector3 unit();

    Vector3 operator-() const { return Vector3(-_x, -_y, -_z); }

        Vector3& operator+=(const Vector3 &v) {
            _x += v._x;
            _y += v._y;
            _z += v._z;
            return *this;
        }

        Vector3& operator*=(const double t) {
            _x *= t;
            _y *= t;
            _z *= t;
            return *this;
        }

        Vector3& operator/=(const double t) {
            return *this *= 1/t;
        }
};

// Vector3 Utility Functions

inline std::ostream& operator<<(std::ostream &out, Vector3 v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline Vector3 operator+(Vector3 u, Vector3 v) {
    return Vector3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vector3 operator-(Vector3 u, Vector3 v) {
    return Vector3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vector3 operator*(Vector3 u, Vector3 v) {
    return Vector3(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vector3 operator*(double t, Vector3 v) {
    return Vector3(t*v.x(), t*v.y(), t*v.z());
}

inline Vector3 operator*(const Vector3 &v, double t) {
    return t * v;
}

inline Vector3 operator/(Vector3 v, double t) {
    return (1/t) * v;
}

inline double dot(Vector3 u, Vector3 v) {
    return u.x() * v.x()
         + u.y() * v.y()
         + u.z() * v.z();
}

inline Vector3 cross(Vector3 u, Vector3 v) {
    return Vector3(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline Vector3 random_in_unit_disk() {
    while (true) {
        auto p = Vector3(random_double(-1,1), random_double(-1,1), 0);
        if (p.length_squared() >= 1) continue;
        return p;
    }
}

inline Vector3 reflect(Vector3 v, Vector3 n) {
    return v - 2 * dot(v,n) * n;
}

Vector3 refract(Vector3 uv, Vector3 n, double etai_over_etat);

#endif