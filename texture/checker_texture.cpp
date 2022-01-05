#include "checker_texture.h"

Vector3 checker_texture::value(double u, double v, Vector3 P) {
    auto sines = sin(10*P.x())*sin(10*P.y())*sin(10*P.z());
    if (sines < 0)
        return _odd->value(u, v, P);
    else
        return _even->value(u, v, P);
}