#include "sphere.h"
#include <cmath>

Sphere::Sphere() {}

Sphere::Sphere(Vector3d center, double radius, std::shared_ptr<Material> material_ptr){
    center_ = center;
    radius_ = radius;
    material_ptr_ = material_ptr;
};

Vector3d Sphere::center() {
    return center_;
};

double Sphere::radius() {
    return radius_;
}

bool Sphere::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    Vector3d oc = r.origin() - center_;
    auto a = Dot(r.direction(), r.direction());
    auto half_b = Dot(oc, r.direction());
    auto c = Dot(oc, oc) - radius_ * radius_;
    auto discriminant = half_b * half_b - a * c;
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
    Vector3d outward_normal = (rec.point - center_) / radius_;
    rec.set_face_normal(r, outward_normal);
    GetSphereUV(outward_normal, rec.u, rec.v);
    rec.material_ptr = material_ptr_;

    return true;
}


bool Sphere::BoundingBox(double time0, double time1, AABB& output_box) {
    output_box = AABB(
        center_ - Vector3d(radius_, radius_, radius_),
        center_ + Vector3d(radius_, radius_, radius_));
    return true;
}

void Sphere::GetSphereUV(Vector3d P, double& u, double& v) {
    auto theta = acos(-P.y());
    auto phi = atan2(-P.z(), P.x()) + kPi;

    u = phi / (2 * kPi);
    v = theta / kPi;
}