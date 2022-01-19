#ifndef CONSTANT_MEDIUM_H
#define CONSTANT_MEDIUM_H

#include "../common.h"
#include "hittable.h"
#include "../texture/texture.h"
#include "../material/isotropic.h"

class ConstantMedium : public Hittable {
    private:
        std::shared_ptr<Hittable> boundary_;
        std::shared_ptr<Material> phase_function_;
        double neg_inv_density_;
    
    public:
        ConstantMedium(std::shared_ptr<Hittable> boundary, double d, std::shared_ptr<Texture> a)
            : boundary_(boundary),
              neg_inv_density_(-1/d),
              phase_function_(std::make_shared<Isotropic>(a)){}
            
        ConstantMedium(std::shared_ptr<Hittable> boundary, double d, Vector3d color)
            : boundary_(boundary),
              neg_inv_density_(-1/d),
              phase_function_(std::make_shared<Isotropic>(color)){}
        
        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool BoundingBox(double time0, double time1, AABB& output_box) override {
            return boundary_->BoundingBox(time0, time1, output_box);
        }
};

#endif