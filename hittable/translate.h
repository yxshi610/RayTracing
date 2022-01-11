#ifndef TRANSLATE_H
#define TRANSLATE_H

#include "../main.h"
#include "./hittable.h"

class Translate : public hittable {
    private:
        std::shared_ptr<hittable> _ptr;
        Vector3 _offset;
    
    public:
        Translate(std::shared_ptr<hittable> ptr, Vector3 offset): _ptr(ptr), _offset(offset) {}

        virtual bool hit (Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) override;
};

#endif