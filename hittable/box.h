#ifndef BOX_H
#define BOX_H

#include "../main.h"
#include "hittable_list.h"

class box : public hittable {
    private:
        Vector3 _box_min;
        Vector3 _box_max;
        hittable_list _sides;
    
    public:
        box() {}
        box(Vector3 p0, Vector3 p1, std::shared_ptr<material> ptr);

        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;

        virtual bool bounding_box(double time0, double time1, aabb& output_box) override {
            output_box = aabb(_box_min, _box_max);
            return true;
        }
};

#endif