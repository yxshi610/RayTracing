#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include "../common.h"
#include "texture.h"
#include "./solid_color.h"

class CheckerTexture : public Texture {
    private:
        std::shared_ptr<Texture> odd_;
        std::shared_ptr<Texture> even_;
    
    public:
        CheckerTexture();
        CheckerTexture(std::shared_ptr<Texture> even, std::shared_ptr<Texture> odd)
            : even_(even), odd_(odd) {}
        CheckerTexture(Vector3d c1, Vector3d c2)
            : even_(std::make_shared<SolidColor>(c1)) , odd_(std::make_shared<SolidColor>(c2)) {}

        Vector3d value(double u, double v, Vector3d P);
};

#endif