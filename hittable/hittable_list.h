#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"
#include "../ray.h"
#include "aabb.h"
#include <vector>
#include <memory>

class HittableList : public Hittable {
private:
    std::vector<std::shared_ptr<Hittable>> objects_;

public:
    HittableList();
    HittableList(std::shared_ptr<Hittable> object);

    std::vector<std::shared_ptr<Hittable>> objects();

    void add(std::shared_ptr<Hittable> object);
    void clear();

    bool hit(Ray r, double t_min, double t_max, hit_record& rec);
    bool BoundingBox(double time0, double time1, AABB& output_box);
};

#endif