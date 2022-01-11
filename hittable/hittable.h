#ifndef HITTABLE_H
#define HITTABLE_H

#include "../main.h"
#include "./aabb.h"

class material;

struct hit_record {
    Vector3 point;
    Vector3 normal;
    std::shared_ptr<material> mat_ptr;
    double t;
    double u;
    double v;   // (u, v) texture coordinates [0, 1]
    bool front_face;

    inline void set_face_normal(Ray r, Vector3 outward_normal) {
        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class hittable {
public:
    virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) = 0;
    virtual bool bounding_box(double time0, double time1, aabb& output_box) = 0;
};
#endif