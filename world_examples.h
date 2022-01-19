#ifndef WORLD_EXAMPLES_H
#define WORLD_EXAMPLES_H

#include "hittable/hittable_list.h"
#include "texture/checker_texture.h"
#include "hittable/sphere.h"
#include "hittable/moving_sphere.h"
#include "material/metal.h"
#include "material/dielectric.h"
#include "material/lambertian.h"
#include "texture/noise_texture.h"
#include "texture/image_texture.h"
#include "material/diffuse_light.h"
#include "hittable/aa_rectangle.h"
#include "hittable/Box.h"
#include "hittable/translate.h"
#include "hittable/rotate.h"
#include "hittable/constant_medium.h"
#include "hittable/bvh_node.h"

HittableList RandomScene() {
    HittableList world;

    auto checker = std::make_shared<CheckerTexture>(Vector3d(0.2, 0.3, 0.1), Vector3d(0.9, 0.9, 0.9));
    world.add(std::make_shared<Sphere>(Vector3d(0,-1000,0), 1000, std::make_shared<Lambertian>(checker)));

    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            auto choose_mat = RandomDouble();
            Vector3d center(a + 0.9 * RandomDouble(), 0.2, b + 0.9 * RandomDouble());

            if ((center - Vector3d(4, 0.2, 0)).Length() > 0.9) {
                std::shared_ptr<Material> Sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = Vector3d::Random() * Vector3d::Random();
                    Sphere_material = std::make_shared<Lambertian>(albedo);
                    auto center2 = center + Vector3d(0, RandomDouble(0,.5), 0);
                    world.add(std::make_shared<MovingSphere>(
                        center, center2, 0.0, 1.0, 0.2, Sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = Vector3d::Random(0.5, 1);
                    auto fuzz = RandomDouble(0, 0.5);
                    Sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, Sphere_material));
                } else {
                    // glass
                    Sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, Sphere_material));
                }
            }
        }
    }
    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(Vector3d(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(Vector3d(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(Vector3d(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(Vector3d(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(Vector3d(4, 1, 0), 1.0, material3));
    return world;
}

HittableList TwoSpheres() {
    HittableList objects;

    auto checker = std::make_shared<CheckerTexture>(Vector3d(0.2, 0.3, 0.1), Vector3d(0.9, 0.9, 0.9));

    objects.add(std::make_shared<Sphere>(Vector3d(0,-10, 0), 10, std::make_shared<Lambertian>(checker)));
    objects.add(std::make_shared<Sphere>(Vector3d(0, 10, 0), 10, std::make_shared<Lambertian>(checker)));

    return objects;
}

HittableList TwoPerlinSpheres() {
    HittableList objects;

    auto pertext = std::make_shared<NoiseTexture>(4);
    objects.add(std::make_shared<Sphere>(Vector3d(0,-1000,0), 1000, std::make_shared<Lambertian>(pertext)));
    objects.add(std::make_shared<Sphere>(Vector3d(0, 2, 0), 2, std::make_shared<Lambertian>(pertext)));

    return objects;
}

HittableList Earth() {
    auto earth_texture = std::make_shared<ImageTexture>("texture/imgs/earthmap.jpg");
    auto earth_surface = std::make_shared<Lambertian>(earth_texture);
    auto globe = std::make_shared<Sphere>(Vector3d(0,0,0), 2, earth_surface);

    return HittableList(globe);
}

HittableList SimpleLight() {
    HittableList objects;

    auto pertext = std::make_shared<NoiseTexture>(4);
    objects.add(std::make_shared<Sphere>(Vector3d(0,-1000,0), 1000, std::make_shared<Lambertian>(pertext)));
    objects.add(std::make_shared<Sphere>(Vector3d(0,2,0), 2, std::make_shared<Lambertian>(pertext)));

    auto difflight = std::make_shared<DiffuseLight>(Vector3d(4,4,4));
    objects.add(std::make_shared<XYRectangle>(3, 5, 1, 3, -2, difflight));

    return objects;
}

HittableList CornellBox() {
    HittableList objects;

    auto red   = std::make_shared<Lambertian>(Vector3d(.65, .05, .05));
    auto white = std::make_shared<Lambertian>(Vector3d(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(Vector3d(.12, .45, .15));
    auto light = std::make_shared<DiffuseLight>(Vector3d(15, 15, 15));

    objects.add(std::make_shared<YZRectangle>(0, 555, 0, 555, 555, green));
    objects.add(std::make_shared<YZRectangle>(0, 555, 0, 555, 0, red));
    objects.add(std::make_shared<XZRectangle>(213, 343, 227, 332, 554, light));
    objects.add(std::make_shared<XZRectangle>(0, 555, 0, 555, 0, white));
    objects.add(std::make_shared<XZRectangle>(0, 555, 0, 555, 555, white));
    objects.add(std::make_shared<XYRectangle>(0, 555, 0, 555, 555, white));

    std::shared_ptr<Hittable> box1 = std::make_shared<Box>(Vector3d(0, 0, 0), Vector3d(165, 330, 165), white);
    box1 = std::make_shared<YRotate>(box1, 15);
    box1 = std::make_shared<Translate>(box1, Vector3d(265,0,295));
    objects.add(box1);

    std::shared_ptr<Hittable> box2 = std::make_shared<Box>(Vector3d(0,0,0), Vector3d(165,165,165), white);
    box2 = std::make_shared<YRotate>(box2, -18);
    box2 = std::make_shared<Translate>(box2, Vector3d(130,0,65));
    objects.add(box2);

    return objects;
}

HittableList CornellSmoke() {
    HittableList objects;

    auto red   = std::make_shared<Lambertian>(Vector3d(.65, .05, .05));
    auto white = std::make_shared<Lambertian>(Vector3d(.73, .73, .73));
    auto green = std::make_shared<Lambertian>(Vector3d(.12, .45, .15));
    auto light = std::make_shared<DiffuseLight>(Vector3d(7, 7, 7));

    objects.add(std::make_shared<YZRectangle>(0, 555, 0, 555, 555, green));
    objects.add(std::make_shared<YZRectangle>(0, 555, 0, 555, 0, red));
    objects.add(std::make_shared<XZRectangle>(213, 343, 227, 332, 554, light));
    objects.add(std::make_shared<XZRectangle>(0, 555, 0, 555, 0, white));
    objects.add(std::make_shared<XZRectangle>(0, 555, 0, 555, 555, white));
    objects.add(std::make_shared<XYRectangle>(0, 555, 0, 555, 555, white));

    std::shared_ptr<Hittable> box1 = std::make_shared<Box>(Vector3d(0, 0, 0), Vector3d(165, 330, 165), white);
    box1 = std::make_shared<YRotate>(box1, 15);
    box1 = std::make_shared<Translate>(box1, Vector3d(265,0,295));

    std::shared_ptr<Hittable> box2 = std::make_shared<Box>(Vector3d(0,0,0), Vector3d(165,165,165), white);
    box2 = std::make_shared<YRotate>(box2, -18);
    box2 = std::make_shared<Translate>(box2, Vector3d(130,0,65));

    objects.add(std::make_shared<ConstantMedium>(box1, 0.01, Vector3d(0,0,0)));
    objects.add(std::make_shared<ConstantMedium>(box2, 0.01, Vector3d(1,1,1)));

    return objects;
}

HittableList FinalScene() {
    HittableList boxes1;
    auto ground = std::make_shared<Lambertian>(Vector3d(0.48, 0.83, 0.53));

    const int boxes_per_side = 20;
    for (int i = 0; i < boxes_per_side; i++) {
        for (int j = 0; j < boxes_per_side; j++) {
            auto w = 100.0;
            auto x0 = -1000.0 + i*w;
            auto z0 = -1000.0 + j*w;
            auto y0 = 0.0;
            auto x1 = x0 + w;
            auto y1 = RandomDouble(1,101);
            auto z1 = z0 + w;

            boxes1.add(std::make_shared<Box>(Vector3d(x0,y0,z0), Vector3d(x1,y1,z1), ground));
        }
    }

    HittableList objects;

    objects.add(std::make_shared<BVHNode>(boxes1, 0, 1));

    auto light = std::make_shared<DiffuseLight>(Vector3d(7, 7, 7));
    objects.add(std::make_shared<XZRectangle>(123, 423, 147, 412, 554, light));

    auto center1 = Vector3d(400, 400, 200);
    auto center2 = center1 + Vector3d(30,0,0);
    auto moving_Sphere_material = std::make_shared<Lambertian>(Vector3d(0.7, 0.3, 0.1));
    objects.add(std::make_shared<MovingSphere>(center1, center2, 0, 1, 50, moving_Sphere_material));

    objects.add(std::make_shared<Sphere>(Vector3d(260, 150, 45), 50, std::make_shared<Dielectric>(1.5)));
    objects.add(std::make_shared<Sphere>(
        Vector3d(0, 150, 145), 50, std::make_shared<Metal>(Vector3d(0.8, 0.8, 0.9), 1.0)
    ));

    auto boundary = std::make_shared<Sphere>(Vector3d(360,150,145), 70, std::make_shared<Dielectric>(1.5));
    objects.add(boundary);
    objects.add(std::make_shared<ConstantMedium>(boundary, 0.2, Vector3d(0.2, 0.4, 0.9)));
    boundary = std::make_shared<Sphere>(Vector3d(0, 0, 0), 5000, std::make_shared<Dielectric>(1.5));
    objects.add(std::make_shared<ConstantMedium>(boundary, .0001, Vector3d(1,1,1)));

    auto emat = std::make_shared<Lambertian>(std::make_shared<ImageTexture>("texture/imgs/earthmap.jpg"));
    objects.add(std::make_shared<Sphere>(Vector3d(400,200,400), 100, emat));
    auto pertext = std::make_shared<NoiseTexture>(0.1);
    objects.add(std::make_shared<Sphere>(Vector3d(220,280,300), 80, std::make_shared<Lambertian>(pertext)));

    HittableList boxes2;
    auto white = std::make_shared<Lambertian>(Vector3d(.73, .73, .73));
    int ns = 1000;
    for (int j = 0; j < ns; j++) {
        boxes2.add(std::make_shared<Sphere>(Vector3d::Random(0,165), 10, white));
    }

    objects.add(std::make_shared<Translate>(
        std::make_shared<YRotate>(
            std::make_shared<BVHNode>(boxes2, 0.0, 1.0), 15),
            Vector3d(-100,270,395)
        )
    );

    return objects;
}

#endif