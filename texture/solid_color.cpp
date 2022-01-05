#include "solid_color.h"

solid_color::solid_color() {}
solid_color::solid_color(Vector3 color) {
    _color_value = color;
}
solid_color::solid_color(double red, double green, double blue) {
    solid_color(Vector3(red, green, blue));
}

Vector3 solid_color::value(double u, double v, Vector3 P) {
    return _color_value;
}