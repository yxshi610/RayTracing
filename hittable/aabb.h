#ifndef AABB_H
#define AABB_H

#include "../main.h"

class aabb {
    private:
        Vector3 _minimum;
        Vector3 _maximum;

    public:
        aabb();
        aabb(Vector3 minimum, Vector3 maximum);

        Vector3 min();
        Vector3 max();

        bool hit(Ray r, double t_min, double t_max);
};

aabb surrounding_box(aabb box0, aabb box1);

#endif