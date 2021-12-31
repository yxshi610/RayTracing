#ifndef SPHERE_H
#define SPHERE_H

#include "Vector3.h"
#include "hittable.h"

class Sphere : public Hittable {
private:
    Vector3 _center;
    double _radius;
public:
    Sphere(Vector3 center, double radius);

    Vector3 center(){};
    double radius(){};

    virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) const override;
};

#endif