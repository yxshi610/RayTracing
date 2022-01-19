#ifndef AA_RECTANGLE_H
#define AA_RECTANGLE_H

#include "hittable.h"

class XYRectangle : public Hittable {
    private:
        std::shared_ptr<Material> material_;
        double x0_, x1_, y0_, y1_, k_;

    public:
        XYRectangle() {}
        XYRectangle(double x0, double x1, double y0, double y1, double k, std::shared_ptr<Material> material):
            x0_(x0), x1_(x1), y0_(y0), y1_(y1), k_(k), material_(material) {};
        
        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool BoundingBox(double time0, double time1, AABB& output_box) override {
            // The bounding box must have non-zero width in each dimension, so pad the Z
            // dimension a small amount.
            output_box = AABB(Vector3d(x0_, y0_, k_ - 0.0001), Vector3d(x1_, y1_, k_ + 0.0001));
            return true;
        }

};

class XZRectangle : public Hittable {
    private:
        std::shared_ptr<Material> material_;
        double x0_, x1_, _z0, _z1, k_;

    public:
        XZRectangle() {}
        XZRectangle(double x0, double x1, double z0, double z1, double k, std::shared_ptr<Material> material):
            x0_(x0), x1_(x1), _z0(z0), _z1(z1), k_(k), material_(material) {};
        
        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool BoundingBox(double time0, double time1, AABB& output_box) override {
            // The bounding box must have non-zero width in each dimension, so pad the Y
            // dimension a small amount.
            output_box = AABB(Vector3d(x0_, _z0, k_ - 0.0001), Vector3d(x1_, _z1, k_ + 0.0001));
            return true;
        }
};

class YZRectangle : public Hittable {
    private:
        std::shared_ptr<Material> material_;
        double y0_, y1_, _z0, _z1, k_;

    public:
        YZRectangle() {}
        YZRectangle(double y0, double y1, double z0, double z1, double k, std::shared_ptr<Material> material):
            y0_(y0), y1_(y1), _z0(z0), _z1(z1), k_(k), material_(material) {};
        
        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool BoundingBox(double time0, double time1, AABB& output_box) override {
            // The bounding box must have non-zero width in each dimension, so pad the X
            // dimension a small amount.
            output_box = AABB(Vector3d(y0_, _z0, k_ - 0.0001), Vector3d(y1_, _z1, k_ + 0.0001));
            return true;
        }
};

#endif