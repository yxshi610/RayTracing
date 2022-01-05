#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "../main.h"
#include "hittable.h"
#include "aabb.h"
#include <vector>
#include <memory>

class hittable_list : public hittable {
private:
    std::vector<std::shared_ptr<hittable>> _objects;

public:
    hittable_list();
    hittable_list(std::shared_ptr<hittable> object);

    std::vector<std::shared_ptr<hittable>> objects();

    void add(std::shared_ptr<hittable> object);
    void clear();

    bool hit(Ray r, double t_min, double t_max, hit_record& rec);
    bool bounding_box(double time0, double time1, aabb& output_box);
};

#endif