#include "main.h"

#include "Sphere.h"
#include "hittable_list.h"
#include "camera.h"
#include <iostream>

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

Vector3 ray_color(Ray r, hittable_list world, int depth) {
    hit_record rec;

    if (depth <= 0) return Vector3(0, 0, 0);

    if (world.hit(r, 0.001, infinity, rec)) {
        Vector3 target = rec.P + rec.N + Vector3::random_in_unit_sphere();
        return 0.5 * ray_color(Ray(rec.P, target - rec.P), world, depth - 1);
    }
    Vector3 unit_direction = r.direction().unit();
    auto t = 0.5*(unit_direction.y() + 1.0);
    return (1.0-t)*Vector3(1.0, 1.0, 1.0) + t*Vector3(0.5, 0.7, 1.0);
}

void write_color(std::ostream &out, Vector3 pixel_color, int samples_per_pixel) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Divide the color by the number of samples and gamma-correct for gamma=2.0.
    auto scale = 1.0 / samples_per_pixel;
    r = sqrt(scale * r);
    g = sqrt(scale * g);
    b = sqrt(scale * b);

    // Write the translated [0,255] value of each color component.
    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

int main() {
  // Image
    const auto aspect_ratio = 16.0 / 9.0;
    const int image_width = 400;
    const int image_height = static_cast<int>(image_width / aspect_ratio);
    const int samples_per_pixel = 100;
    const int max_depth = 50;

    // World
    hittable_list world;
    world.add(std::make_shared<Sphere>(Vector3(0,0,-1), 0.5));
    world.add(std::make_shared<Sphere>(Vector3(0,-100.5,-1), 100));

    // Camera

    camera cam;

    // Render
    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {
            Vector3 pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + random_double()) / (image_width-1);
                auto v = (j + random_double()) / (image_height-1);
                Ray r = cam.get_ray(u, v);
                pixel_color = pixel_color + ray_color(r, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}