#include "ray.h"

Ray::Ray() {}

Ray::Ray(Vector3d origin, Vector3d direction, double time) {
    origin_ = origin;
    direction_ = direction;
    time_ = time;
}

Vector3d Ray::origin() {
    return origin_;
}

Vector3d Ray::direction() {
    return direction_;
}

Vector3d Ray::At(double t) {
    return origin_ + t * direction_;
}

double Ray::time() {
    return time_;
}