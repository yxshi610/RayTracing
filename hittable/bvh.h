#ifndef BVH_H
#define BVH_H

#include "../main.h"

#include "hittable.h"
#include "hittable_list.h"

class bvh_node : public hittable {
    private:
        std::shared_ptr<hittable> _left;
        std::shared_ptr<hittable> _right;
        aabb _box;

    public:
        bvh_node();
        bvh_node(hittable_list list, double time0, double time1)
            : bvh_node(list.objects(), 0, list.objects().size(), time0, time1)
        {}

        bvh_node(
            std::vector<std::shared_ptr<hittable>> src_objects,
            std::size_t start, std::size_t end, double time0, double time1);

        bool hit(Ray r, double t_min, double t_max, hit_record& rec);
        bool bounding_box(double time0, double time1, aabb& output_box);
};

inline bool box_compare(std::shared_ptr<hittable> a, std::shared_ptr<hittable> b, int axis) {
    aabb box_a;
    aabb box_b;

    if (!a->bounding_box(0,0, box_a) || !b->bounding_box(0,0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";
    switch (axis) {
        case 0:
            return box_a.min().x() < box_b.min().x();
        case 1:
            return box_a.min().y() < box_b.min().y();
        case 2:
            return box_a.min().z() < box_b.min().z();
    }
}

inline bool box_x_compare (std::shared_ptr<hittable> a, std::shared_ptr<hittable> b) {
    return box_compare(a, b, 0);
}

inline bool box_y_compare (std::shared_ptr<hittable> a, std::shared_ptr<hittable> b) {
    return box_compare(a, b, 1);
}

inline bool box_z_compare (std::shared_ptr<hittable> a, std::shared_ptr<hittable> b) {
    return box_compare(a, b, 2);
}

#endif