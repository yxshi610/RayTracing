#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "texture.h"

class solid_color : public texture {
    private:
        Vector3 _color_value;

    public:
        solid_color();
        solid_color(Vector3 color);
        solid_color(double red, double green, double blue);

        Vector3 value(double u, double v, Vector3 P) override;
};

#endif