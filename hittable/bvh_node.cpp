#include "bvh_node.h"
#include <algorithm>

BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>> src_objects, std::size_t start, std::size_t end, double time0, double time1) {
    auto objects = src_objects;

    int axis = RandomInt(0,2);
    auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        left_ = right_ = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            left_ = objects[start];
            right_ = objects[start+1];
        } else {
            left_ = objects[start+1];
            right_ = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span/2;
        left_ = std::make_shared<BVHNode>(objects, start, mid, time0, time1);
        right_ = std::make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB boxleft_, boxright_;

    if (  !left_->BoundingBox (time0, time1, boxleft_)
       || !right_->BoundingBox(time0, time1, boxright_)
    )
        std::cerr << "No bounding box in BVHNode constructor.\n";

    box_ = SurroundingBox(boxleft_, boxright_);
}

bool BVHNode::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    if (!box_.hit(r, t_min, t_max))
        return false;

    bool hitleft_ = left_->hit(r, t_min, t_max, rec);
    bool hitright_ = right_->hit(r, t_min, hitleft_ ? rec.t : t_max, rec);

    return hitleft_ || hitright_;
}

bool BVHNode::BoundingBox(double time0, double time1, AABB& outputbox_) {
    outputbox_ = box_;
    return true;
}