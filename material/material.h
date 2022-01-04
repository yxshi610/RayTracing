#ifndef MATERIAL_H
#define MATERIAL_H

#include "../main.h"

struct hit_record;

class material {
public:
    virtual bool scatter(
            Ray r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered
        ) const = 0;
};

class lambertian: public material {
private:
    Vector3 albedo;

public:
    lambertian(Vector3 a) : albedo(a) {}

    virtual bool scatter(
        Ray r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered
    ) const override {
        auto scatter_direction = rec.N + Vector3::random_unit_sphere();

        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.N;

        scattered = Ray(rec.P, scatter_direction);
        attenuation = albedo;
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
        Ray r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered
    ) const override {
        Vector3 reflected = reflect(r_in.direction().unit(), rec.N);
        scattered = Ray(rec.P, reflected + _fuzz * Vector3::random_in_unit_sphere());
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
            Ray r_in, const hit_record& rec, Vector3& attenuation, Ray& scattered
        ) const override {
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

            scattered = Ray(rec.P, direction);
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