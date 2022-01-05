#ifndef MOVING_SPHERE_H
#define MOVING_SPHERE_H

#include "../main.h"
#include "./hittable.h"
#include "./aabb.h"

class moving_sphere : public hittable {
    private:
        Vector3 _center0, _center1;
        double _time0, _time1;
        double _radius;
        std::shared_ptr<material> _mat_ptr;

    public:
        moving_sphere();
        moving_sphere(Vector3 center0, Vector3 center1, double time0, double time1, double radius, std::shared_ptr<material> m);

        Vector3 center(double time);

        bool hit(Ray r, double t_min, double t_max, hit_record& rec);
        bool bounding_box(double _time0, double _time1, aabb& output_box);
};

#endif