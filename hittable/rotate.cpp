#include "rotate.h"

YRotate::YRotate(std::shared_ptr<Hittable> p, double angle) : ptr_(p) {
    auto radians = DegreesToRadians(angle);
    sin_theta_ = sin(radians);
    cos_theta_ = cos(radians);
    hasbox_ = ptr_->BoundingBox(0, 1, bbox_);

    double x = kInfinity, y = kInfinity, z = kInfinity;
    double X = -kInfinity, Y = -kInfinity, Z = -kInfinity;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto a = i * bbox_.max().x() + (1-i) * bbox_.min().x();
                auto b = j * bbox_.max().y() + (1-j) * bbox_.min().y();
                auto c = k * bbox_.max().z() + (1-k) * bbox_.min().z();

                auto newx =  cos_theta_ * a + sin_theta_ * c;
                auto newz = -sin_theta_ * a + cos_theta_ * c;

                Vector3d tester(newx, b, newz);

                x = fmin(x, tester.x());
                y = fmin(y, tester.y());
                z = fmin(z, tester.z());
                X = fmax(X, tester.x());
                Y = fmax(Y, tester.y());
                Z = fmax(Z, tester.z());
            }
        }
    }

    bbox_ = AABB(Vector3d(x, y, z), Vector3d(X, Y, Z));
}

bool YRotate::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    auto origin = r.origin();
    auto direction = r.direction();

    auto originX = cos_theta_ * r.origin().x() - sin_theta_ * r.origin().z();
    auto originZ = sin_theta_ * r.origin().x() + cos_theta_ * r.origin().z();

    auto directionX = cos_theta_ * r.direction().x() - sin_theta_ * r.direction().z();
    auto directionZ = sin_theta_ * r.direction().x() + cos_theta_ * r.direction().z();

    Ray rotated_r(Vector3d(originX, origin.y(), originZ), Vector3d(directionX, direction.y(), directionZ), r.time());

    if (!ptr_->hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.point;
    auto normal = rec.normal;

    p.set(-cos_theta_ * rec.point.x() + sin_theta_ * rec.point.z(), p.y(), -sin_theta_ * rec.point.x() + cos_theta_ * rec.point.z());

    normal.set(cos_theta_ * rec.normal.x() + sin_theta_ * rec.normal.z(), normal.y(), -sin_theta_ * rec.normal.x() + cos_theta_ * rec.normal.z());

    rec.point = p;
    rec.set_face_normal(rotated_r, normal);

    return true;
}