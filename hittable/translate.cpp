#include "translate.h"

bool Translate::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    Ray moved_r(r.origin() - offset_, r.direction(), r.time());
    if (!ptr_->hit(moved_r, t_min, t_max, rec)) return false;

    rec.point += offset_;
    rec.set_face_normal(moved_r, rec.normal);

    return true;
}

bool Translate::BoundingBox(double time0, double time1, AABB& output_box) {
    if (!ptr_->BoundingBox(time0, time1, output_box)) return false;

    output_box = AABB(output_box.min() + offset_, output_box.max() + offset_);
    
    return true;
}