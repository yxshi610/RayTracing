#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "perlin.h"
#include "texture.h"

class noise_texture : public texture {
    private:
        perlin noise;
        double _scale;
    
    public:
        noise_texture() {};
        noise_texture(double scale) :_scale(scale) {}

        virtual Vector3 value(double u, double v, Vector3 p) override {
            return Vector3(1, 1, 1) * 0.5 * (1 + sin(_scale*p.z() + 10*noise.turb(p)));
        }
};

#endif