#ifndef  AABB_H
#define  AABB_H

#include "../common.h"

class  AABB {
    private:
        Vector3d minimum_;
        Vector3d maximum_;

    public:
        AABB();
        AABB(Vector3d minimum, Vector3d maximum);

        Vector3d min();
        Vector3d max();

        bool hit(Ray r, double t_min, double t_max);
};

 AABB SurroundingBox(AABB box0,  AABB box1);

#endif