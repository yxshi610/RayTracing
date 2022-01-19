#include "image_texture.h"
// TODO: why can not move this to image_texture.h
#include "use_stb_image.h"

ImageTexture::ImageTexture(): data_(nullptr), width_(0), height_(0), bytes_per_scanline_(0) {}
ImageTexture::ImageTexture(const char* filename) {
    auto components_per_pixel = bytes_per_scanline_;
    data_ = stbi_load(filename, &width_, &height_, &components_per_pixel, components_per_pixel);
    if (!data_) {
        std::cerr << "ERROR: Could not load texture image file '" << filename << "'.\n";
        width_ = height_ = 0; 
    }
    bytes_per_scanline_ = bytes_per_pixel * width_;
}
ImageTexture::~ImageTexture(){
    delete data_;
}

Vector3d ImageTexture::value(double u, double v, Vector3d p) {
    // if no texture data.
    if (data_ == nullptr) return Vector3d(0, 1, 1);

    // clamp input texture coordinates to [0, 1] * [0, 1]
    u = Clamp(u, 0.0, 1.0);
    v = 1.0 - Clamp(v, 0.0, 1.0);

    auto i = static_cast<int>(u * width_);
    auto j = static_cast<int>(v * height_);

    // clamp integer mapping, actual coor should be less than 1.0
    if (i >= width_) i = width_ - 1;
    if (j >= height_) j = height_ - 1;

    const auto color_scale = 1.0 / 255.0;
    auto pixel = data_ + j * bytes_per_scanline_ + i * bytes_per_pixel;

    return Vector3d(color_scale * pixel[0], color_scale * pixel[1], color_scale * pixel[2]);
}