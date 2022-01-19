#include "box.h"
#include "aa_rectangle.h"

Box::Box(Vector3d p0, Vector3d p1, std::shared_ptr<Material> ptr) {
    box_min_ = p0;
    box_max_ = p1;

    sides_.add(std::make_shared<XYRectangle>(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr));
    sides_.add(std::make_shared<XYRectangle>(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));

    sides_.add(std::make_shared<XZRectangle>(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr));
    sides_.add(std::make_shared<XZRectangle>(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));

    sides_.add(std::make_shared<YZRectangle>(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr));
    sides_.add(std::make_shared<YZRectangle>(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
}

bool Box::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    return sides_.hit(r, t_min, t_max, rec);
}