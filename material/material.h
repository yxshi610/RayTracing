#ifndef MATERIAL_H
#define MATERIAL_H

#include "../main.h"
#include "../texture/solid_color.h"

struct hit_record;

class material {
    public:
        // for non-emitting, return black.
        virtual Vector3 emitted(double u, double v, Vector3 p) {
            return Vector3(0, 0, 0);
        }
        
        virtual bool scatter(
                Ray r_in, hit_record& rec, Vector3& attenuation, Ray& scattered
            ) = 0;
};

class lambertian: public material {
private:
    std::shared_ptr<texture> albedo;

public:
    lambertian(Vector3 a) : albedo(std::make_shared<solid_color>(a)) {}
    lambertian(std::shared_ptr<texture> a) : albedo(a) {}

    virtual bool scatter(
        Ray r_in, hit_record& rec, Vector3& attenuation, Ray& scattered
    ) override {
        auto scatter_direction = rec.N + Vector3::random_unit_sphere();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.N;

        scattered = Ray(rec.P, scatter_direction, r_in.time());
        attenuation = albedo->value(rec.u, rec.v, rec.P);
        return true;
    }
};

class metal: public material {
private:
    Vector3 _albedo;
    double _fuzz;

public:
    metal(Vector3 albedo, double fuzz) : _albedo(albedo), _fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(
        Ray r_in, hit_record& rec, Vector3& attenuation, Ray& scattered
    ) override {
        Vector3 reflected = reflect(r_in.direction().unit(), rec.N);
        scattered = Ray(rec.P, reflected + _fuzz * Vector3::random_in_unit_sphere(), r_in.time());
        attenuation = _albedo;
        return (dot(scattered.direction(), rec.N) > 0);
    }
};

class dielectric : public material {
    private:
        double ir; // Index of Refraction

    public:
        dielectric(double index_of_refraction) : ir(index_of_refraction) {}

        virtual bool scatter(
            Ray r_in, hit_record& rec, Vector3& attenuation, Ray& scattered
        ) override {
            attenuation = Vector3(1.0, 1.0, 1.0);
            double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

            Vector3 unit_direction = r_in.direction().unit();
            double cos_theta = fmin(dot(-unit_direction, rec.N), 1.0);
            double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

            bool cannot_refract = refraction_ratio * sin_theta > 1.0;
            Vector3 direction;

            if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double())
                direction = reflect(unit_direction, rec.N);
            else
                direction = refract(unit_direction, rec.N, refraction_ratio);

            scattered = Ray(rec.P, direction, r_in.time());
            return true;
        }
    
    private:
        static double reflectance(double cosine, double ref_idx) {
            // Use Schlick's approximation for reflectance.
            auto r0 = (1-ref_idx) / (1+ref_idx);
            r0 = r0*r0;
            return r0 + (1-r0)*pow((1 - cosine),5);
        }
};

#endif