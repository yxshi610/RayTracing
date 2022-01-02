#ifndef HITTABLE_H
#define HITTABLE_H

#include "../main.h"

class material;

struct hit_record {
    Vector3 P;
    Vector3 N;
    std::shared_ptr<material> mat_ptr;
    double t;
    bool front_face;

    inline void set_face_normal(Ray r, Vector3 outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        N = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) = 0;
};
#endif