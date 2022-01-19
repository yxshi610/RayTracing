#include "hittable_list.h"

HittableList::HittableList() {}

HittableList::HittableList(std::shared_ptr<Hittable> object) {
    add(object);
}

std::vector<std::shared_ptr<Hittable>> HittableList::objects() {
    return objects_;
}

void HittableList::add(std::shared_ptr<Hittable> object) {
    objects_.push_back(object);
}

void HittableList::clear() {
    objects_.clear();
}

bool HittableList::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = t_max;

    for (auto object : objects_) {
        // object is <shared_ptr>, like node -> value.
        if (object->hit(r, t_min, closest_so_far, temp_rec)) {
            hit_anything = true;
            closest_so_far = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_anything;
}

bool HittableList::BoundingBox(double time0, double time1, AABB& output_box) {
    if (objects_.empty()) return false;

    AABB temp_box;
    bool first_box = true;

    for (const auto& object : objects_) {
        if (!object->BoundingBox(time0, time1, temp_box)) return false;
        output_box = first_box ? temp_box : SurroundingBox(output_box, temp_box);
        first_box = false;
    }

    return true;
}