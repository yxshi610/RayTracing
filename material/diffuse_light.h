#ifndef DIFFUSE_LIGHT_H
#define DIFFUSE_LIGHT_H

#include "material.h"

class DiffuseLight : public material {
    private:
        std::shared_ptr<texture> _emit;

    public:
        DiffuseLight(std::shared_ptr<texture> a) : _emit(a) {}
        DiffuseLight(Vector3 c) : _emit(std::make_shared<solid_color>(c)) {}

        virtual bool scatter (Ray r, hit_record& rec, Vector3& attenuation, Ray& scattered) override {
            return false;
        }

        virtual Vector3 emitted(double u, double v, Vector3 p) override {
            return _emit->value(u, v, p);
        }
};

#endif