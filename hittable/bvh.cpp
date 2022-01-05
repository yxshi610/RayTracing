#include "bvh.h"
#include <algorithm>

bvh_node::bvh_node(std::vector<std::shared_ptr<hittable>> src_objects, std::size_t start, std::size_t end, double time0, double time1) {
    auto objects = src_objects;

    int axis = random_int(0,2);
    auto comparator = (axis == 0) ? box_x_compare
                    : (axis == 1) ? box_y_compare
                                  : box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1) {
        _left = _right = objects[start];
    } else if (object_span == 2) {
        if (comparator(objects[start], objects[start+1])) {
            _left = objects[start];
            _right = objects[start+1];
        } else {
            _left = objects[start+1];
            _right = objects[start];
        }
    } else {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span/2;
        _left = std::make_shared<bvh_node>(objects, start, mid, time0, time1);
        _right = std::make_shared<bvh_node>(objects, mid, end, time0, time1);
    }

    aabb box_left, box_right;

    if (  !_left->bounding_box (time0, time1, box_left)
       || !_right->bounding_box(time0, time1, box_right)
    )
        std::cerr << "No bounding box in bvh_node constructor.\n";

    _box = surrounding_box(box_left, box_right);
}

bool bvh_node::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    if (!_box.hit(r, t_min, t_max))
        return false;

    bool hit_left = _left->hit(r, t_min, t_max, rec);
    bool hit_right = _right->hit(r, t_min, hit_left ? rec.t : t_max, rec);

    return hit_left || hit_right;
}

bool bvh_node::bounding_box(double time0, double time1, aabb& output_box) {
    output_box = _box;
    return true;
}