#ifndef METAL_H
#define METAL_H

#include "material.h"

class Metal : public Material {
    private:
        Vector3d albedo_;
        double fuzz_;
    
    public:
        Metal(Vector3d albedo, double fuzz) : albedo_(albedo), fuzz_(fuzz < 1 ? fuzz : 1) {}

        virtual bool scatter(
            Ray r_in, hit_record& rec, Vector3d& attenuation, Ray& scattered
        ) override {
            Vector3d reflected = Reflect(UnitVector(r_in.direction()), rec.normal);
            scattered = Ray(rec.point, reflected + fuzz_ * Vector3d::RandomInUnitSphere(), r_in.time());
            attenuation = albedo_;
            return (Dot(scattered.direction(), rec.normal) > 0);
        }
};

#endif