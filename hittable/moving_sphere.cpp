#include "moving_sphere.h"

moving_sphere::moving_sphere(){}
moving_sphere::moving_sphere(Vector3 center0, Vector3 center1, double time0, double time1, double radius, std::shared_ptr<material> m) {
    _center0 = center0;
    _center1 = center1;
    _time0 = time0;
    _time1 = time1;
    _radius = radius;
    _mat_ptr = m;
}

Vector3 moving_sphere::center(double time) {
    return _center0 + ((time - _time0) / (_time1 - _time0))*(_center1 - _center0);
}

bool moving_sphere::hit(Ray r, double t_min, double t_max, hit_record &rec) {
    Vector3 oc = r.origin() - center(r.time());
    auto a = r.direction().length_squared();
    auto half_b = dot(oc, r.direction());
    auto c = oc.length_squared() - _radius*_radius;

    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) return false;
    auto sqrtd = sqrt(discriminant);

    // Find the nearest root that lies in the acceptable range.
    auto root = (-half_b - sqrtd) / a;
    if (root < t_min || t_max < root) {
        root = (-half_b + sqrtd) / a;
        if (root < t_min || t_max < root)
            return false;
    }

    rec.t = root;
    rec.point = r.at(rec.t);
    auto outward_normal = (rec.point - center(r.time())) / _radius;
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = _mat_ptr;

    return true;
}

bool moving_sphere::bounding_box(double _time0, double _time1, aabb& output_box) {
    aabb box0(
        center(_time0) - Vector3(_radius, _radius, _radius),
        center(_time0) + Vector3(_radius, _radius, _radius));
    aabb box1(
        center(_time1) - Vector3(_radius, _radius, _radius),
        center(_time1) + Vector3(_radius, _radius, _radius));
    output_box = surrounding_box(box0, box1);
    return true;
}