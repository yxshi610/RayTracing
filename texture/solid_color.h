#ifndef SOLID_COLOR_H
#define SOLID_COLOR_H

#include "texture.h"

class SolidColor : public Texture {
    private:
        Vector3d color_;

    public:
        SolidColor();
        SolidColor(Vector3d color);
        SolidColor(double red, double green, double blue);

        Vector3d value(double u, double v, Vector3d P);
};

#endif