#ifndef TEXTURE_H
#define TEXTURE_H

#include "../common.h"

class Texture {
    public:
        virtual Vector3d value(double u, double v, Vector3d P) = 0;
};

#endif