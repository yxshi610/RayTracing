#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "../common.h"
#include "./hittable.h"

class Translate : public Hittable {
    private:
        std::shared_ptr<Hittable> ptr_;
        Vector3d offset_;
    
    public:
        Translate(std::shared_ptr<Hittable> ptr, Vector3d offset): ptr_(ptr), offset_(offset) {}

        virtual bool hit (Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool BoundingBox(double time0, double time1, AABB& output_box) override;
};

#endif