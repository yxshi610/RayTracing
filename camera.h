#ifndef CAMERA_H
#define CAMERA_H

#include "main.h"

class camera {
private:
    Vector3 _origin;
    Vector3 _lower_left_corner;
    Vector3 _horizontal;
    Vector3 _vertical;
    Vector3 _u, _v, _w;
    double _lens_radius;

public:
    camera(Vector3 lookfrom, Vector3 lookat, Vector3 vup, double vfov, double aspect_ratio, double aperture, double focus_dist);
    Ray get_ray(double s, double t);
};

#endif