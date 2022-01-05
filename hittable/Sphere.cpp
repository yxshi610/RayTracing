#include "sphere.h"
#include <cmath>

sphere::sphere(Vector3 center, double radius, std::shared_ptr<material> mat_ptr){
    _center = center;
    _radius = radius;
    _mat_ptr = mat_ptr;
};

Vector3 sphere::center() {
    return _center;
};

double sphere::radius() {
    return _radius;
}

bool sphere::hit(Ray r, double t_min, double t_max, hit_record& rec) {
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
    get_sphere_uv(outward_normal, rec.u, rec.v);
    rec.mat_ptr = _mat_ptr;

    return true;
}

bool sphere::bounding_box(double time0, double time1, aabb& output_box) {
    output_box = aabb(
        _center - Vector3(_radius, _radius, _radius),
        _center + Vector3(_radius, _radius, _radius));
    return true;
}

void sphere::get_sphere_uv(Vector3 P, double& u, double& v) {
    auto theta = acos(-P.y());
    auto phi = atan2(-P.z(), P.x()) + pi;

    u = phi / (2*pi);
    v = theta / pi;
}