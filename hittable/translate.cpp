#include "translate.h"

bool Translate::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    Ray moved_r(r.origin() - _offset, r.direction(), r.time());
    if (!_ptr->hit(moved_r, t_min, t_max, rec)) return false;

    rec.point += _offset;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}

bool Translate::bounding_box(double time0, double time1, aabb& output_box) {
    if (!_ptr->bounding_box(time0, time1, output_box)) return false;

    output_box = aabb(output_box.min() + _offset, output_box.max() + _offset);
    
    return true;
}