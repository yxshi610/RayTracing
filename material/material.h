#ifndef MATERIAL_H
#define MATERIAL_H

#include "../common.h"
#include "../hittable/hittable.h"

struct hit_record;

class Material {
    public:
        // for non-emitting, return black.
        virtual Vector3d Emitted(double u, double v, Vector3d p) {
            return Vector3d(0, 0, 0);
        }

        virtual bool scatter(
            Ray r_in, hit_record& rec, Vector3d& attenuation, Ray& scattered
        ) = 0;
};

#endif