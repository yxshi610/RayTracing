#include "common.h"

#include "camera.h"
#include "world_examples.h"


#include <iostream>


Vector3d ray_color(Ray r, Vector3d background, HittableList world, int depth) {
    hit_record rec;

    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return Vector3d(0,0,0);

    if (!world.hit(r, 0.001, kInfinity, rec)) return background;

    Ray scattered;
    Vector3d attenuation;
    Vector3d emitted = rec.material_ptr->Emitted(rec.u, rec.v, rec.point);

    if (!rec.material_ptr->scatter(r, rec, attenuation, scattered))
        return emitted;
    
    return emitted + attenuation * ray_color(scattered, background, world, depth-1);
}

int main() {
    // Image
    auto aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int samples_per_pixel = 80;
    const int max_depth = 50;
    Vector3d background(0.70, 0.80, 1.00);

    // Camera
    Vector3d lookfrom = Vector3d(13,2,3);;
    Vector3d lookat = Vector3d(0,0,0);
    Vector3d vup(0, 1, 0);
    auto vfov = 20.0;
    auto aperture = 0.0;
    auto dist_to_focus = 10.0;

    HittableList world;
    switch (0) {
        case 1:
            world = RandomScene();
            aperture = 0.1;
            break;
        case 2:
            world = TwoSpheres();
            break;
        case 3:
            world = TwoPerlinSpheres();
            break;
        case 4:
            world = Earth();
            break;
        case 5:
            world = SimpleLight();
            background = Vector3d(0, 0, 0);
            lookfrom = Vector3d(26, 3, 6);
            lookat = Vector3d(0, 2, 0);
            break;
        case 6:
            world = CornellBox();
            aspect_ratio = 1.0;
            background = Vector3d(0, 0, 0);
            lookfrom = Vector3d(278, 278, -800);
            lookat = Vector3d(278, 278, 0);
            vfov = 40.0;
            break;
        case 7:
            world = CornellSmoke();
            aspect_ratio = 1.0;
            background = Vector3d(0, 0, 0);
            lookfrom = Vector3d(278, 278, -800);
            lookat = Vector3d(278, 278, 0);
            vfov = 40.0;
            break;
        default:
        case 8:
            world = FinalScene();
            aspect_ratio = 1.0;
            image_width = 800;
            samples_per_pixel = 10;
            background = Vector3d(0, 0, 0);
            lookfrom = Vector3d(478, 278, -600);
            lookat = Vector3d(278, 278, 0);
            vfov = 40.0;
            break;
    }

    int image_height = static_cast<int>(image_width / aspect_ratio);
    Camera cam(lookfrom, lookat, vup, vfov, aspect_ratio, aperture, dist_to_focus, 0.0, 1.0);

    // Render

    std::cout << "P3\n" << image_width << " " << image_height << "\n255\n";

    for (int j = image_height-1; j >= 0; --j) {
        std::cerr << "\rScanlines remaining: " << j << ' ' << std::flush;
        for (int i = 0; i < image_width; ++i) {

            Vector3d pixel_color(0, 0, 0);
            for (int s = 0; s < samples_per_pixel; ++s) {
                auto u = (i + RandomDouble()) / (image_width-1);
                auto v = (j + RandomDouble()) / (image_height-1);
                Ray r = cam.get_ray(u, v);
                pixel_color += ray_color(r, background, world, max_depth);
            }
            write_color(std::cout, pixel_color, samples_per_pixel);
        }
    }
    std::cerr << "\nDone.\n";
}