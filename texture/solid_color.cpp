#include "solid_color.h"

SolidColor::SolidColor() {}
SolidColor::SolidColor(Vector3d color) {
    color_ = color;
}
SolidColor::SolidColor(double red, double green, double blue) {
    SolidColor(Vector3d(red, green, blue));
}

Vector3d SolidColor::value(double u, double v, Vector3d P) {
    return color_;
}