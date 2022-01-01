#ifndef CAMERA_H
#define CAMERA_H

#include "main.h"

class camera {
private:
    Vector3 _origin;
    Vector3 _lower_left_corner;
    Vector3 _horizontal;
    Vector3 _vertical;

public:
    camera();
    Ray get_ray(double u, double v);
};

#endif