#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "../common.h"
#include "./hittable.h"
#include "aabb.h"

class MovingSphere : public Hittable {
    private:
        Vector3d center0_, center1_;
        double time0_, time1_;
        double radius_;
        std::shared_ptr<Material> material_ptr_;

    public:
        MovingSphere();
        MovingSphere(Vector3d center0, Vector3d center1, double time0, double time1, double radius, std::shared_ptr<Material> mateiral_ptr);

        Vector3d center(double time);

        bool hit(Ray r, double t_min, double t_max, hit_record& rec);
        bool BoundingBox(double _time0, double _time1, AABB& output_box);
};

#endif