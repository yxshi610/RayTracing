#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "texture.h"

class ImageTexture : public Texture {
    private:
        unsigned char* data_;
        int width_, height_;
        int bytes_per_scanline_;

    public:
        const static int bytes_per_pixel = 3;
        
        ImageTexture();
        ImageTexture(const char* filename);
        ~ImageTexture();
        
        virtual Vector3d value(double u, double v, Vector3d p) override;

};

#endif