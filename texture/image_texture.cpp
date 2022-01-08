#include "image_texture.h"
// TODO: why can not move this to image_texture.h
#include "main_stb_image.h"

ImageTexture::ImageTexture(): _data(nullptr), _width(0), _height(0), _bytes_per_scanline(0) {}
ImageTexture::ImageTexture(const char* filename) {
    auto components_per_pixel = _bytes_per_scanline;
    _data = stbi_load(filename, &_width, &_height, &components_per_pixel, components_per_pixel);
    if (!_data) {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        _width = _height = 0; 
    }
    _bytes_per_scanline = bytes_per_pixel * _width;
}
ImageTexture::~ImageTexture(){
    delete _data;
}

Vector3 ImageTexture::value(double u, double v, Vector3 p) {
    // if no texture data.
    if (_data == nullptr) return Vector3(0, 1, 1);

    // clamp input texture coordinates to [0, 1] * [0, 1]
    u = clamp(u, 0.0, 1.0);
    v = 1.0 - clamp(v, 0.0, 1.0);

    auto i = static_cast<int>(u * _width);
    auto j = static_cast<int>(v * _height);

    // clamp integer mapping, actual coor should be less than 1.0
    if (i >= _width) i = _width - 1;
    if (j >= _height) j = _height - 1;

    const auto color_scale = 1.0 / 255.0;
    auto pixel = _data + j * _bytes_per_scanline + i * bytes_per_pixel;

    return Vector3(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}