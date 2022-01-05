#include "main.h"

Ray::Ray() {}

Ray::Ray(Vector3 origin, Vector3 direction, double time) {
    _origin = origin;
    _direction = direction;
    _time = time;
}

Vector3 Ray::origin() {
    return _origin;
}

Vector3 Ray::direction() {
    return _direction;
}

Vector3 Ray::at(double t) {
    return _origin + t * _direction;
}

double Ray::time() {
    return _time;
}