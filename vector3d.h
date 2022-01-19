#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

class Vector3d {
    private:
        double value_[3];

    public:
        Vector3d();
        Vector3d(double x, double y, double z);
        void set(double x, double y, double z);
        double x();
        double y();
        double z();

        Vector3d operator-();
        double operator[](int i);
        Vector3d& operator+=(Vector3d v);
        Vector3d& operator*=(double t);
        Vector3d& operator/=(double t);

        double Length();
        double LengthSquared();

        static Vector3d Random();
        static Vector3d Random(double min, double max);

        static Vector3d RandomInUnitSphere();
        static Vector3d RandomUnitVector();
        static Vector3d RandomInHemisphere(Vector3d noraml);
        static Vector3d RandomUnitDisk();

        bool NearZero();
};

// Vector3d Utility Functions
inline std::ostream& operator<<(std::ostream &out, Vector3d v) {
    return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline Vector3d operator+(Vector3d u, Vector3d v) {
    return Vector3d(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline Vector3d operator-(Vector3d u, Vector3d v) {
    return Vector3d(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline Vector3d operator*(Vector3d u, Vector3d v) {
    return Vector3d(u.x() * v.x(), u.y() * v.y(), u.z() * v.z());
}

inline Vector3d operator*(double t, Vector3d v) {
    return Vector3d(t*v.x(), t*v.y(), t*v.z());
}

inline Vector3d operator*(Vector3d v, double t) {
    return t * v;
}

inline Vector3d operator/(Vector3d v, double t) {
    return (1/t) * v;
}

inline double Dot(Vector3d u, Vector3d v) {
    return u.x() * v.x()
         + u.y() * v.y()
         + u.z() * v.z();
}

inline Vector3d Cross(Vector3d u, Vector3d v) {
    return Vector3d(u.y() * v.z() - u.z() * v.y(),
                u.z() * v.x() - u.x() * v.z(),
                u.x() * v.y() - u.y() * v.x());
}

inline Vector3d UnitVector(Vector3d v) {
    return v / v.Length();
}


inline Vector3d Reflect(Vector3d v, Vector3d n) {
    return v - 2 * Dot(v,n) * n;
}

Vector3d Refract(Vector3d uv, Vector3d n, double etai_over_etat);

void write_color(std::ostream& out, Vector3d pixel_color, int samples_per_pixel);

#endif