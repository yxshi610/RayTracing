#ifndef SPHERE_H
#define SPHERE_H

#include "../main.h"
#include "hittable.h"

class Sphere : public Hittable {
private:
    Vector3 _center;
    double _radius;
    std::shared_ptr<material> _mat_ptr;
    
public:
    Sphere() {}
    Sphere(Vector3 center, double radius, std::shared_ptr<material> m);

    Vector3 center();
    double radius();

    bool hit(Ray r, double t_min, double t_max, hit_record& rec);
};

#endif