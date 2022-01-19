#ifndef ROTATE_H
#define ROTATE_H

#include "../common.h"
#include "hittable.h"

class YRotate : public Hittable {
    private:
        std::shared_ptr<Hittable> ptr_;
        double sin_theta_;
        double cos_theta_;
        bool hasbox_;
        AABB bbox_;

    public:
        YRotate(std::shared_ptr<Hittable> p, double angle);
        
        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool BoundingBox(double time0, double time1, AABB& output_box) override {
            output_box = bbox_;
            return hasbox_;
        }
};

#endif