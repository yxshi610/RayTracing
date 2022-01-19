#ifndef BOX_H
#define BOX_H

#include "../common.h"
#include "hittable_list.h"

class Box : public Hittable {
    private:
        Vector3d box_min_;
        Vector3d box_max_;
        HittableList sides_;
    
    public:
        Box() {}
        Box(Vector3d p0, Vector3d p1, std::shared_ptr<Material> ptr);

        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;

        virtual bool BoundingBox(double time0, double time1, AABB& output_box) override {
            output_box = AABB(box_min_, box_max_);
            return true;
        }
};

#endif