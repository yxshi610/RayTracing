#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

class Vector3
{
private:
    double _x;
    double _y;
    double _z;

public:
    Vector3(double x = 0, double y = 0, double z = 0);
    void set(double x, double y, double z);
    double x();
    double y();
    double z();

    static double Dot(Vector3 x, Vector3 y);

    double length();
    Vector3 unit();

    Vector3 operator + (Vector3 second) {
        Vector3 res;
        res.set(_x + second.x(), _y + second.y(), _z + second.z());
        return res;
    }

    Vector3 operator - (Vector3 second) {
        Vector3 res;
        res.set(_x - second.x(), _y - second.y(), _z - second.z());
        return res;
    }

    Vector3 operator * (double scale) {
        Vector3 res;
        res.set(_x * scale, _y * scale, _z * scale);
        return res;
    }

    Vector3 operator / (double scale) {
        Vector3 res;
        res.set(_x / scale, _y / scale, _z / scale);
        return res;
    }

    friend inline Vector3 operator * (double scale, Vector3 v) {
        Vector3 res;
        res.set(v.x() * scale, v.y() * scale, v.z() * scale);
        return res;
    }
};

void write_color(std::ostream &out, Vector3 pixel_color);

#endif