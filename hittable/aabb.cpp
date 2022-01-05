#include "aabb.h"

aabb::aabb() {}

aabb::aabb(Vector3 minimum, Vector3 maximum) {
    _minimum = minimum;
    _maximum = maximum;

}

Vector3 aabb::min() {
    return _minimum;
}
Vector3 aabb::max() {
    return _maximum;
}

bool aabb::hit(Ray r, double t_min, double t_max) {
    double minimum[3]; double maximum[3]; double origin[3]; double direction[3];
    minimum[0] = _minimum.x(); minimum[1] = _minimum.y(); minimum[2] = _minimum.z();
    maximum[0] = _maximum.x(); maximum[1] = _maximum.y(); maximum[2] = _maximum.z(); 
    origin[0] = r.origin().x(); origin[1] = r.origin().y(); origin[2] = r.origin().z();
    direction[0] = r.direction().x(); direction[1] = r.direction().y(); direction[2] = r.direction().z(); 
    for (int a = 0; a < 3; a++) {
        auto invD = 1.0f / direction[a];
        auto t0 = (minimum[a] - origin[a]) * invD;
        auto t1 = (maximum[a] - origin[a]) * invD;
        if (invD < 0.0f)
            std::swap(t0, t1);
        t_min = t0 > t_min ? t0 : t_min;
        t_max = t1 < t_max ? t1 : t_max;
        if (t_max <= t_min)
            return false;
    }
    return true;
}

aabb surrounding_box(aabb box0, aabb box1) {
    Vector3 small(fmin(box0.min().x(), box1.min().x()),
                 fmin(box0.min().y(), box1.min().y()),
                 fmin(box0.min().z(), box1.min().z()));

    Vector3 big(fmax(box0.max().x(), box1.max().x()),
               fmax(box0.max().y(), box1.max().y()),
               fmax(box0.max().z(), box1.max().z()));

    return aabb(small,big);
}