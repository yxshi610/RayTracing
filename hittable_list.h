#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "main.h"
#include "hittable.h"
#include <vector>
#include <memory>

class hittable_list : public Hittable {
private:
    std::vector<std::shared_ptr<Hittable>> _objects;

public:
    hittable_list();
    hittable_list(std::shared_ptr<Hittable> object);

    void add(std::shared_ptr<Hittable> object);
    void clear();

    bool hit(Ray r, double t_min, double t_max, hit_record& rec);
};

#endif