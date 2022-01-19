#ifndef NOISE_TEXTURE_H
#define NOISE_TEXTURE_H

#include "perlin.h"
#include "texture.h"

class NoiseTexture : public Texture {
    private:
        Perlin noise_;
        double scale_;
    
    public:
        NoiseTexture() {};
        NoiseTexture(double scale) :scale_(scale) {}

        virtual Vector3d value(double u, double v, Vector3d p) override {
            return Vector3d(1, 1, 1) * 0.5 * (1 + sin(scale_*p.z() + 10*noise_.Turb(p)));
        }
};

#endif