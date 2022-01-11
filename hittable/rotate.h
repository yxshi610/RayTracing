#ifndef ROTATE_H
#define ROTATE_H

#include "../main.h"
#include "hittable.h"

class YRotate : public hittable {
    private:
        std::shared_ptr<hittable> _ptr;
        double _sin_theta;
        double _cos_theta;
        bool _hasbox;
        aabb _bbox;

    public:
        YRotate(std::shared_ptr<hittable> p, double angle);
        
        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) override {
            output_box = _bbox;
            return _hasbox;
        }
};

#endif