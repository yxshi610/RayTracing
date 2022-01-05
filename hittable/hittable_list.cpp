#include "hittable_list.h"

hittable_list::hittable_list() {}

hittable_list::hittable_list(std::shared_ptr<hittable> object) {
    add(object);
}

std::vector<std::shared_ptr<hittable>> hittable_list::objects() {
    return _objects;
}

void hittable_list::add(std::shared_ptr<hittable> object) {
    _objects.push_back(object);
}

void hittable_list::clear() {
    _objects.clear();
}

bool hittable_list::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (const auto& object : _objects) {
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

bool hittable_list::bounding_box(double time0, double time1, aabb& output_box) {
    if (_objects.empty()) return false;

    aabb temp_box;
    bool first_box = true;

    for (const auto& object : _objects) {
        if (!object->bounding_box(time0, time1, temp_box)) return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}