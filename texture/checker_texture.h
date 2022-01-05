#ifndef CHECKER_TEXTURE_H
#define CHECKER_TEXTURE_H

#include "../main.h"
#include "texture.h"
#include "./solid_color.h"

class checker_texture : public texture {
    private:
        std::shared_ptr<texture> _odd;
        std::shared_ptr<texture> _even;
    
    public:
        checker_texture();
        checker_texture(std::shared_ptr<texture> even, std::shared_ptr<texture> odd)
            : _even(even), _odd(odd) {}
        checker_texture(Vector3 c1, Vector3 c2)
            : _even(std::make_shared<solid_color>(c1)) , _odd(std::make_shared<solid_color>(c2)) {}

        virtual Vector3 value(double u, double v, Vector3 P) override;
};

#endif