#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "../main.h"
#include "hittable.h"
#include "../texture/texture.h"
#include "../material/material.h"

class ConstantMedium : public hittable {
    private:
        std::shared_ptr<hittable> boundary_;
        std::shared_ptr<material> phase_function_;
        double neg_inv_density_;
    
    public:
        ConstantMedium(std::shared_ptr<hittable> boundary, double d, std::shared_ptr<texture> a)
            : boundary_(boundary),
              neg_inv_density_(-1/d),
              phase_function_(std::make_shared<Isotropic>(a)){}
            
        ConstantMedium(std::shared_ptr<hittable> boundary, double d, Vector3 color)
            : boundary_(boundary),
              neg_inv_density_(-1/d),
              phase_function_(std::make_shared<Isotropic>(color)){}
        
        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) override {
            return boundary_->bounding_box(time0, time1, output_box);
        }
};

#endif