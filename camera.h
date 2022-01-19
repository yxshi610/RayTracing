#ifndef CAMERA_H
#define CAMERA_H

#include "common.h"

class Camera {
private:
    Vector3d origin_;
    Vector3d lower_left_corner_;
    Vector3d horizontal_;
    Vector3d vertical_;
    Vector3d u_, v_, w_;
    double lens_radius_;
    double time0_, time1_;

public:
Camera();
    Camera(Vector3d lookfrom, Vector3d lookat, Vector3d vup, double vfov, double aspect_ratio, double aperture, double focus_dist, double time0 = 0, double time1 = 0);
    Ray get_ray(double s, double t);
};

#endif