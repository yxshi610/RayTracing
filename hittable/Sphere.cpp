#include "Sphere.h"
#include <cmath>

Sphere::Sphere(Vector3 center, double radius, std::shared_ptr<material> mat_ptr){
    _center = center;
    _radius = radius;
    _mat_ptr = mat_ptr;
};

Vector3 Sphere::center() {
    return _center;
};

double Sphere::radius() {
    return _radius;
}

bool Sphere::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    Vector3 oc = r.origin() - _center;
    auto a = dot(r.direction(), r.direction());
    auto half_b = dot(oc, r.direction());
    auto c = dot(oc, oc) - _radius*_radius;
    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;

    auto sqrtd = std::sqrt(discriminant);
    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.P = r.at(rec.t);
    Vector3 outward_normal = (rec.P - _center) / _radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = _mat_ptr;

    return true;
}

