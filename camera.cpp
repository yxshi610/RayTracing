#include "camera.h"

Camera::Camera(Vector3d lookfrom, Vector3d lookat, Vector3d vup, double vfov, double aspect_ratio, double aperture, double focus_dist, double time0, double time1) {
    auto theta = DegreesToRadians(vfov);
    auto h = tan(theta/2);
    auto viewport_height = 2.0 * h;
    auto viewport_width = aspect_ratio * viewport_height;

    w_ = UnitVector((lookfrom - lookat));
    u_ = UnitVector(Cross(vup, w_));
    v_ = Cross(w_, u_);

    origin_ = lookfrom;
    horizontal_ = focus_dist * viewport_width * u_;
    vertical_ = focus_dist * viewport_height * v_;
    lower_left_corner_ = origin_ - horizontal_/2 - vertical_/2 - focus_dist * w_;

    lens_radius_ = aperture / 2;
    time0_ = time0;
    time1_ = time1;
}

Ray Camera::get_ray(double s, double t) {
    Vector3d rd = lens_radius_ * Vector3d::RandomUnitDisk();
    Vector3d offset = u_ * rd.x() + v_ * rd.y();

    return Ray(origin_ + offset, 
            lower_left_corner_ + s * horizontal_ + t * vertical_ - origin_ - offset,
            RandomDouble(time0_, time1_));
}