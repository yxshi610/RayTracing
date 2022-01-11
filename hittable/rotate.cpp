#include "rotate.h"

YRotate::YRotate(std::shared_ptr<hittable> p, double angle) : _ptr(p) {
    auto radians = degrees_to_radians(angle);
    _sin_theta = sin(radians);
    _cos_theta = cos(radians);
    _hasbox = _ptr->bounding_box(0, 1, _bbox);

    double x = infinity, y = infinity, z = infinity;
    double X = -infinity, Y = -infinity, Z = -infinity;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                auto a = i * _bbox.max().x() + (1-i) * _bbox.min().x();
                auto b = j * _bbox.max().y() + (1-j) * _bbox.min().y();
                auto c = k * _bbox.max().z() + (1-k) * _bbox.min().z();

                auto newx =  _cos_theta * a + _sin_theta * c;
                auto newz = -_sin_theta * a + _cos_theta * c;

                Vector3 tester(newx, b, newz);

                x = fmin(x, tester.x());
                y = fmin(y, tester.y());
                z = fmin(z, tester.z());
                X = fmax(X, tester.x());
                Y = fmax(Y, tester.y());
                Z = fmax(Z, tester.z());
            }
        }
    }

    _bbox = aabb(Vector3(x, y, z), Vector3(X, Y, Z));
}

bool YRotate::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    auto origin = r.origin();
    auto direction = r.direction();

    auto originX = _cos_theta * r.origin().x() - _sin_theta * r.origin().z();
    auto originZ = _sin_theta * r.origin().x() + _cos_theta * r.origin().z();

    auto directionX = _cos_theta * r.direction().x() - _sin_theta * r.direction().z();
    auto directionZ = _sin_theta * r.direction().x() + _cos_theta * r.direction().z();

    Ray rotated_r(Vector3(originX, origin.y(), originZ), Vector3(directionX, direction.y(), directionZ), r.time());

    if (!_ptr->hit(rotated_r, t_min, t_max, rec))
        return false;

    auto p = rec.point;
    auto normal = rec.normal;

    p.set(-_cos_theta * rec.point.x() + _sin_theta * rec.point.z(), p.y(), -_sin_theta * rec.point.x() + _cos_theta * rec.point.z());

    normal.set(_cos_theta * rec.normal.x() + _sin_theta * rec.normal.z(), normal.y(), -_sin_theta * rec.normal.x() + _cos_theta * rec.normal.z());

    rec.point = p;
    rec.set_face_normal(rotated_r, normal);

    return true;
}