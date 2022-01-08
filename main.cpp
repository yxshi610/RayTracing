#include "main.h"

#include "camera.h"
#include "./hittable/hittable_list.h"
#include "./material/material.h"
#include "./hittable/sphere.h"
#include "./hittable/moving_sphere.h"
#include "./texture/checker_texture.h"
#include "./texture/noise_texture.h"
#include "./texture/image_texture.h"
#include "./material/diffuse_light.h"
#include "./hittable/aa_rectangle.h"

#include <iostream>

double hit_sphere(Vector3 center, double radius, Ray r) {
    Vector3 oc = r.origin() - center;
    auto a = dot(r.direction(), r.direction());
    auto half_b = dot(oc, r.direction());
    auto c = dot(oc, oc) - radius*radius;
    auto discriminant = half_b*half_b - a*c;
    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-half_b - std::sqrt(discriminant) ) / a;
    }
}

Vector3 ray_color(Ray r, Vector3 background, hittable_list world, int depth) {
    hit_record rec;

    if (depth <= 0) return Vector3(0, 0, 0);

    if (!world.hit(r, 0.001, infinity, rec)) return background;

        Ray scattered;
        Vector3 attenuation;
        Vector3 emitted = rec.mat_ptr->emitted(rec.u, rec.v, rec.P);

        if (!rec.mat_ptr->scatter(r, rec, attenuation, scattered)) return emitted;
        
        return emitted + attenuation * ray_color(scattered, background, world, depth-1);

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

hittable_list random_scene() {
    hittable_list world;

    auto checker = std::make_shared<checker_texture>(Vector3(0.2, 0.3, 0.1), Vector3(0.9, 0.9, 0.9));
    world.add(std::make_shared<sphere>(Vector3(0,-1000,0), 1000, std::make_shared<lambertian>(checker)));

    for (int a = -3; a < 3; a++) {
        for (int b = -3; b < 3; b++) {
            auto choose_mat = random_double();
            Vector3 center(a + 0.9*random_double(), 0.2, b + 0.9*random_double());

            if ((center - Vector3(4, 0.2, 0)).length() > 0.9) {
                std::shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Vector3::random() * Vector3::random();
                    sphere_material = std::make_shared<lambertian>(albedo);
                    auto center2 = center + Vector3(0, random_double(0,.5), 0);
                    world.add(std::make_shared<moving_sphere>(
                        center, center2, 0.0, 1.0, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Vector3::random(0.5, 1);
                    auto fuzz = random_double(0, 0.5);
                    sphere_material = std::make_shared<metal>(albedo, fuzz);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = std::make_shared<dielectric>(1.5);
                    world.add(std::make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }
    return world;
}

hittable_list two_perlin_spheres() {
    hittable_list objects;

    auto pertext = std::make_shared<noise_texture>(4);
    objects.add(std::make_shared<sphere>(Vector3(0,-1000,0), 1000, std::make_shared<lambertian>(pertext)));
    objects.add(std::make_shared<sphere>(Vector3(0, 2, 0), 2, std::make_shared<lambertian>(pertext)));

    return objects;
}

hittable_list earth() {
    auto earth_texture = std::make_shared<ImageTexture>("bella.jpg");
    auto earth_surface = std::make_shared<lambertian>(earth_texture);
    auto globe = std::make_shared<sphere>(Vector3(0,0,0), 2, earth_surface);

    return hittable_list(globe);
}

hittable_list simple_light() {
    hittable_list objects;

    auto pertext = std::make_shared<noise_texture>(4);
    objects.add(std::make_shared<sphere>(Vector3(0,-1000,0), 1000, std::make_shared<lambertian>(pertext)));
    objects.add(std::make_shared<sphere>(Vector3(0,2,0), 2, std::make_shared<lambertian>(pertext)));

    auto difflight = std::make_shared<DiffuseLight>(Vector3(4,4,4));
    objects.add(std::make_shared<XYRectangle>(3, 5, 1, 3, -2, difflight));

    return objects;
}

hittable_list cornell_box() {
    hittable_list objects;

    auto red   = std::make_shared<lambertian>(Vector3(.65, .05, .05));
    auto white = std::make_shared<lambertian>(Vector3(.73, .73, .73));
    auto green = std::make_shared<lambertian>(Vector3(.12, .45, .15));
    auto light = std::make_shared<DiffuseLight>(Vector3(15, 15, 15));

    objects.add(std::make_shared<YZRectangle>(0, 555, 0, 555, 555, green));
    objects.add(std::make_shared<YZRectangle>(0, 555, 0, 555, 0, red));
    objects.add(std::make_shared<XZRectangle>(213, 343, 227, 332, 554, light));
    objects.add(std::make_shared<XZRectangle>(0, 555, 0, 555, 0, white));
    objects.add(std::make_shared<XZRectangle>(0, 555, 0, 555, 555, white));
    objects.add(std::make_shared<XYRectangle>(0, 555, 0, 555, 555, white));

    return objects;
}

int main() {
    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 100;
    int max_depth = 50;

    // Camera1
    Vector3 lookfrom;
    Vector3 lookat;
    auto vfov = 40.0;
    auto aperture = 0.0;

    // World
    Vector3 background(0, 0, 0);

    hittable_list world;

    switch (0) {
        case 1:
            break;
        case 2:
            break;
        case 3:
            background = Vector3(0.70, 0.80, 1.00);
            world = two_perlin_spheres();
            break;
        case 4:
            background = Vector3(0.70, 0.80, 1.00);
            world = earth();
            break;
        case 5:
            world = simple_light();
            samples_per_pixel = 400;
            background = Vector3(0.0, 0.0, 0.0);
            break;
        default:
        case 6 :
            world = cornell_box();
            aspect_ratio = 1.0;
            image_width = 600;
            samples_per_pixel = 200;
            background = Vector3(0,0,0);
            lookfrom = Vector3(278, 278, -800);
            lookat = Vector3(278, 278, 0);
            vfov = 40.0;
            break;
    }

    // Camera

    const Vector3 vup(0,1,0);
    const auto dist_to_focus = 10.0;
    const int image_height = static_cast<int>(image_width / aspect_ratio);

    camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

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
                pixel_color = pixel_color + ray_color(r, background, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }

    std::cerr << "\nDone.\n";
}