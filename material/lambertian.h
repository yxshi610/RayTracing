#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "material.h"
#include "../texture/solid_color.h"

class Lambertian : public Material {
    private:
        std::shared_ptr<Texture> albedo_;

    public:
        Lambertian(Vector3d color) : albedo_(std::make_shared<SolidColor>(color)) {}
        Lambertian(std::shared_ptr<Texture> color) : albedo_(color) {}

        virtual bool scatter(
            Ray r_in, hit_record& rec, Vector3d& attenuation, Ray& scattered
        ) override {
            auto scatter_direction = rec.normal + Vector3d::RandomUnitVector();

            if (scatter_direction.NearZero())
                scatter_direction = rec.normal;

            scattered = Ray(rec.point, scatter_direction, r_in.time());
            attenuation = albedo_->value(rec.u, rec.v, rec.point);
            return true;
        }
};

#endif