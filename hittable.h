#ifndef HITTABLE_H
#define HITTABLE_H

#include "Vector3.h"
#include "Ray.h"

struct hit_record {
    Vector3 P;
    Vector3 N;
    double t;
    bool front_face;
};

class Hittable {
    virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) const;
};
#endif