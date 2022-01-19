#include "checker_texture.h"

Vector3d CheckerTexture::value(double u, double v, Vector3d P) {
    auto sines = sin(10*P.x())*sin(10*P.y())*sin(10*P.z());
    if (sines < 0)
        return odd_->value(u, v, P);
    else
        return even_->value(u, v, P);
}