#ifndef DIELECTRIC_H
#define DIELECTRIC_H

#include "material.h"

class Dielectric : public Material {
    private:
        double index_of_refraction_; // Index of Refraction

    public:
        Dielectric(double index_of_refraction) : index_of_refraction_(index_of_refraction) {}

        virtual bool scatter(
                Ray r_in, hit_record& rec, Vector3d& attenuation, Ray& scattered
            ) override {
            attenuation = Vector3d(1.0, 1.0, 1.0);
            double refraction_ratio = rec.front_face ? (1.0/index_of_refraction_) : index_of_refraction_;

            Vector3d unit_direction = UnitVector(r_in.direction());
            double cos_theta = fmin(Dot(-unit_direction, rec.normal), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            Vector3d direction;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > RandomDouble())
                direction = Reflect(unit_direction, rec.normal);
            else
                direction = Refract(unit_direction, rec.normal, refraction_ratio);

            scattered = Ray(rec.point, direction, r_in.time());
            return true;
        }
    
    private:
        static double reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1 - ref_idx) / (1 + ref_idx);
            r0 = r0 * r0;
            return r0 + (1 - r0)*pow((1 - cosine),5);
        }
};

#endif