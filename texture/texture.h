#ifndef TEXTURE_H
#define TEXTURE_H

#include "../main.h"

class texture {
    public:
        virtual Vector3 value(double u, double v, Vector3 P) = 0;
};

#endif