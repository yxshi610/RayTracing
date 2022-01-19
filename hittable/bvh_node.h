#ifndef BVH_NODE_H
#define BVH_NODE_H

#include "../common.h"

#include "hittable.h"
#include "hittable_list.h"

class BVHNode : public Hittable {
    private:
        std::shared_ptr<Hittable> left_;
        std::shared_ptr<Hittable> right_;
        AABB box_;

    public:
        BVHNode();
        BVHNode(HittableList list, double time0, double time1)
            : BVHNode(list.objects(), 0, list.objects().size(), time0, time1)
        {}

        BVHNode(
            std::vector<std::shared_ptr<Hittable>> src_objects,
            std::size_t start, std::size_t end, double time0, double time1);

        bool hit(Ray r, double t_min, double t_max, hit_record& rec);
        bool BoundingBox(double time0, double time1, AABB& output_box);
};

inline bool box_compare(std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b, int axis) {
    AABB box_a;
    AABB box_b;

    if (!a->BoundingBox(0,0, box_a) || !b->BoundingBox(0,0, box_b))
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

inline bool box_x_compare (std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
    return box_compare(a, b, 0);
}

inline bool box_y_compare (std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
    return box_compare(a, b, 1);
}

inline bool box_z_compare (std::shared_ptr<Hittable> a, std::shared_ptr<Hittable> b) {
    return box_compare(a, b, 2);
}

#endif