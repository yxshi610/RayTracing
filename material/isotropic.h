#ifndef ISOTROPIC_H
#define ISOTROPIC_H

#include "material.h"
#include "../texture/solid_color.h"

class Isotropic : public Material {
    private:
        std::shared_ptr<Texture> albedo;

    public:
        Isotropic(Vector3d color) : albedo(std::make_shared<SolidColor>(color)) {}
        Isotropic(std::shared_ptr<Texture> a) : albedo(a) {}

        virtual bool scatter(Ray r_in, hit_record& rec, Vector3d& attenuation, Ray& scattered) override {
            scattered = Ray(rec.point, Vector3d::RandomInUnitSphere(), r_in.time());
            attenuation = albedo->value(rec.u, rec.v, rec.point);
            return true;
        }
};

#endif