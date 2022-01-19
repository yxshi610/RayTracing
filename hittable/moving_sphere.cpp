#include "moving_sphere.h"

MovingSphere::MovingSphere(){}
MovingSphere::MovingSphere(Vector3d center0, Vector3d center1, double time0, double time1, double radius, std::shared_ptr<Material> material_ptr) {
    center0_ = center0;
    center1_ = center1;
    time0_ = time0;
    time1_ = time1;
    radius_ = radius;
    material_ptr_ = material_ptr;
}

Vector3d MovingSphere::center(double time) {
    return center0_ + ((time - time0_) / (time1_ - time0_))*(center1_ - center0_);
}

bool MovingSphere::hit(Ray r, double t_min, double t_max, hit_record &rec) {
    Vector3d oc = r.origin() - center(r.time());
    auto a = r.direction().LengthSquared();
    auto half_b = Dot(oc, r.direction());
    auto c = oc.LengthSquared() - radius_ * radius_;

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
    rec.point = r.At(rec.t);
    auto outward_normal = (rec.point - center(r.time())) / radius_;
    rec.set_face_normal(r, outward_normal);
    rec.material_ptr = material_ptr_;

    return true;
}

bool MovingSphere::BoundingBox(double time0, double time1, AABB& output_box) {
    AABB box0(
        center(time0) - Vector3d(radius_, radius_, radius_),
        center(time0) + Vector3d(radius_, radius_, radius_));
    AABB box1(
        center(time1) - Vector3d(radius_, radius_, radius_),
        center(time1) + Vector3d(radius_, radius_, radius_));
    output_box = SurroundingBox(box0, box1);
    return true;
}