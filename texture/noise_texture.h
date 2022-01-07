#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "perlin.h"
#include "texture.h"

class noise_texture : public texture {
    private:
        perlin noise;
    
    public:
        noise_texture() {};

        virtual Vector3 value(double u, double v, Vector3 p) override {
            return Vector3(1, 1, 1) * noise.noise(p);
        }
};

#endif