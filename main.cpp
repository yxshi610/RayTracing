#include <iostream>
#include <cmath>
#include "Vector3.h"
#include "Ray.h"

double hit_sphere(Vector3 center, double radius, Ray r) {
    Vector3 oc = r.origin() - center;
    auto a = Vector3::Dot(r.direction(), r.direction());
    auto half_b = Vector3::Dot(oc, r.direction());
    auto c = Vector3::Dot(oc, oc) - radius*radius;
    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - std::sqrt(discriminant) ) / a;
    }
}

Vector3 ray_color(Ray r) {
    auto t = hit_sphere(Vector3(0, 0, -1), 0.5, r);
    if (t > 0.0) {
        Vector3 N = (r.at(t) - Vector3(0, 0, -1)).unit();
        return 0.5 * Vector3(N.x() + 1, N.y() +1, N.z() +1);
    }
    Vector3 unit_direction = r.direction().unit();
    t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Vector3(1.0, 1.0, 1.0) + t*Vector3(0.5, 0.7, 1.0);
}

int main() {
  // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    // Camera

    auto viewport_height = 2.0;
    auto viewport_width = aspect_ratio * viewport_height;
    auto focal_length = 1.0;

    auto origin = Vector3(0, 0, 0);
    auto horizontal = Vector3(viewport_width, 0, 0);
    auto vertical = Vector3(0, viewport_height, 0);
    auto lower_left_corner = origin - horizontal/2 - vertical/2 - Vector3(0, 0, focal_length);

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            auto u = double(i) / (image_width-1);
            auto v = double(j) / (image_height-1);
            Ray r(origin, lower_left_corner + u*horizontal + v*vertical - origin);
            Vector3 pixel_color = ray_color(r);
            write_color(std::cout, pixel_color);
        }
    }

    std::cerr << "\nDone.\n";
}