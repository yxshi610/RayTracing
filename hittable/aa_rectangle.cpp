#include "aa_rectangle.h"

bool XYRectangle::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    auto t = (_k - r.origin().z()) / r.direction().z();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin().x() + t * r.direction().x();
    auto y = r.origin().y() + t * r.direction().y();
    if (x < _x0 || x > _x1 || y < _y0 || y > _y1)
        return false;
    rec.u = (x - _x0)/(_x1 - _x0);
    rec.v = (y - _y0)/(_y1 - _y0);
    rec.t = t;
    auto outward_normal = Vector3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = _material;
    rec.point = r.at(t);
    return true;
}

bool XZRectangle::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    auto t = (_k - r.origin().y()) / r.direction().y();
    if (t < t_min || t > t_max)
        return false;
    auto x = r.origin().x() + t * r.direction().x();
    auto z = r.origin().z() + t * r.direction().z();
    if (x < _x0 || x > _x1 || z < _z0 || z > _z1)
        return false;
    rec.u = (x - _x0)/(_x1 - _x0);
    rec.v = (z - _z0)/(_z1 - _z0);
    rec.t = t;
    auto outward_normal = Vector3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = _material;
    rec.point = r.at(t);
    return true;
}

bool YZRectangle::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    auto t = (_k - r.origin().x()) / r.direction().x();
    if (t < t_min || t > t_max)
        return false;
    auto y = r.origin().y() + t * r.direction().y();
    auto z = r.origin().z() + t * r.direction().z();
    if (y < _y0 || y > _y1 || z < _z0 || z > _z1)
        return false;
    rec.u = (y - _y0)/(_y1 - _y0);
    rec.v = (z - _z0)/(_z1 - _z0);
    rec.t = t;
    auto outward_normal = Vector3(0, 0, 1);
    rec.set_face_normal(r, outward_normal);
    rec.mat_ptr = _material;
    rec.point = r.at(t);
    return true;
}