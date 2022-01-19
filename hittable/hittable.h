#ifndef HITTABLE_H
#define HITTABLE_H

#include "../common.h"
#include "aabb.h"

class Material;

struct hit_record {
    Vector3d point;
    Vector3d normal;
    double t;

    std::shared_ptr<Material> material_ptr;
    // (u, v) texture coordinates [0, 1]
    double u;
    double v;

    // decide to have the normals always point againt the ray.
    // true if ray is outside the sphere, which means dot product < 0.0
    // TODO: not quite sure why need this.
    bool front_face;

    // e.g. Vector3d outward_normal = (rec.point - center) / radius;
    inline void set_face_normal(Ray r, Vector3d outward_normal) {
        front_face = Dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable {
public:
    virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) = 0;
    virtual bool BoundingBox(double time0, double time1, AABB& output_box) = 0;
};
#endif