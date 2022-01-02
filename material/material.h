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

#endif