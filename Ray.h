#ifndef RAY_H
#define RAY_H

#include "vector3d.h"

class Ray {
private:
    Vector3d origin_;
    Vector3d direction_;
    double time_;

public:
    Ray();
    Ray(Vector3d origin, Vector3d direction, double time = 0.0);
    Vector3d origin();
    Vector3d direction();
    Vector3d At(double t);
    double time();
};

#endif