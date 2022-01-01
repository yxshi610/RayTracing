#include "hittable_list.h"

hittable_list::hittable_list() {}

hittable_list::hittable_list(std::shared_ptr<Hittable> object) {
    add(object);
}

void hittable_list::add(std::shared_ptr<Hittable> object) {
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