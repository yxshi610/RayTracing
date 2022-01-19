#include "aa_rectangle.h"

bool XYRectangle::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    auto t = (k_ - r.origin().z()) / r.direction().z();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin().x() + t * r.direction().x();
    auto y = r.origin().y() + t * r.direction().y();
    if (x < x0_ || x > x1_ || y < y0_ || y > y1_)
        return false;
    rec.u = (x - x0_)/(x1_ - x0_);
    rec.v = (y - y0_)/(y1_ - y0_);
    rec.t = t;
    auto outward_normal = Vector3d(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = material_;
    rec.point = r.At(t);
    return true;
}

bool XZRectangle::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    auto t = (k_ - r.origin().y()) / r.direction().y();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin().x() + t * r.direction().x();
    auto z = r.origin().z() + t * r.direction().z();
    if (x < x0_ || x > x1_ || z < _z0 || z > _z1)
        return false;
    rec.u = (x - x0_)/(x1_ - x0_);
    rec.v = (z - _z0)/(_z1 - _z0);
    rec.t = t;
    auto outward_normal = Vector3d(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = material_;
    rec.point = r.At(t);
    return true;
}

bool YZRectangle::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    auto t = (k_ - r.origin().x()) / r.direction().x();
    if (t < t_min || t > t_max)
        return false;
    auto y = r.origin().y() + t * r.direction().y();
    auto z = r.origin().z() + t * r.direction().z();
    if (y < y0_ || y > y1_ || z < _z0 || z > _z1)
        return false;
    rec.u = (y - y0_)/(y1_ - y0_);
    rec.v = (z - _z0)/(_z1 - _z0);
    rec.t = t;
    auto outward_normal = Vector3d(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = material_;
    rec.point = r.At(t);
    return true;
}