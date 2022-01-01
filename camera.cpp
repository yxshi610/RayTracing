#include "camera.h"

camera::camera() {
    auto aspect_ratio = 16.0 / 9.0;
    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    _origin = Vector3(0, 0, 0);
    _horizontal = Vector3(viewport_width, 0.0, 0.0);
    _vertical = Vector3(0.0, viewport_height, 0.0);
    _lower_left_corner = _origin - _horizontal/2 - _vertical/2 - Vector3(0, 0, focal_length);
}

Ray camera::get_ray(double u, double v) {
    return Ray(_origin, _lower_left_corner + u * _horizontal + v * _vertical - _origin);
}