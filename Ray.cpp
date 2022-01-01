#include "main.h"

Ray::Ray(Vector3 origin, Vector3 direction) {
    _origin = origin;
    _direction = direction;
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