#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "material.h"
#include "../texture/solid_color.h"

class DiffuseLight : public Material {
    private:
        std::shared_ptr<Texture> emit_;

    public:
        DiffuseLight(std::shared_ptr<Texture> a) : emit_(a) {}
        DiffuseLight(Vector3d c) : emit_(std::make_shared<SolidColor>(c)) {}

        virtual bool scatter (Ray r, hit_record& rec, Vector3d& attenuation, Ray& scattered) override {
            return false;
        }

        virtual Vector3d Emitted(double u, double v, Vector3d p) override {
            return emit_->value(u, v, p);
        }
};

#endif