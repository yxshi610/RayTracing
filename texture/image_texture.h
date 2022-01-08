#ifndef IMAGE_TEXTURE_H
#define IMAGE_TEXTURE_H

#include "texture.h"

class ImageTexture : public texture {
    private:
        unsigned char* _data;
        int _width, _height;
        int _bytes_per_scanline;

    public:
        const static int bytes_per_pixel = 3;
        
        ImageTexture();
        ImageTexture(const char* filename);
        ~ImageTexture();
        
        virtual Vector3 value(double u, double v, Vector3 p) override;

};

#endif