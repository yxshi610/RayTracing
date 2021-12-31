#ifndef RAY_H
#define RAY_H
#include "Vector3.h"

class Ray {
private:
    Vector3 _origin;
    Vector3 _direction;

public:
    Ray(Vector3 origin, Vector3 direction);
    Vector3 origin();
    Vector3 direction();
    Vector3 at(double t);
};

Vector3 ray_color(Ray r);

#endif