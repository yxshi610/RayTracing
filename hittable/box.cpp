#include "box.h"
#include "aa_rectangle.h"

box::box(Vector3 p0, Vector3 p1, std::shared_ptr<material> ptr) {
    _box_min = p0;
    _box_max = p1;

    _sides.add(std::make_shared<XYRectangle>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    _sides.add(std::make_shared<XYRectangle>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    _sides.add(std::make_shared<XZRectangle>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    _sides.add(std::make_shared<XZRectangle>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    _sides.add(std::make_shared<YZRectangle>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
    _sides.add(std::make_shared<YZRectangle>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
}

bool box::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    return _sides.hit(r, t_min, t_max, rec);
}