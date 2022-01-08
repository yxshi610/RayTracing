#ifndef AA_RECTANGLE_H
#define AA_RECTANGLE_H

#include "hittable.h"

class XYRectangle : public hittable {
    private:
        std::shared_ptr<material> _material;
        double _x0, _x1, _y0, _y1, _k;

    public:
        XYRectangle() {}
        XYRectangle(double x0, double x1, double y0, double y1, double k, std::shared_ptr<material> material):
            _x0(x0), _x1(x1), _y0(y0), _y1(y1), _k(k), _material(material) {};
        
        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) override {
            // The bounding box must have non-zero width in each dimension, so pad the Z
            // dimension a small amount.
            output_box = aabb(Vector3(_x0, _y0, _k - 0.0001), Vector3(_x1, _y1, _k + 0.0001));
            return true;
        }

};

class XZRectangle : public hittable {
    private:
        std::shared_ptr<material> _material;
        double _x0, _x1, _z0, _z1, _k;

    public:
        XZRectangle() {}
        XZRectangle(double x0, double x1, double z0, double z1, double k, std::shared_ptr<material> material):
            _x0(x0), _x1(x1), _z0(z0), _z1(z1), _k(k), _material(material) {};
        
        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) override {
            // The bounding box must have non-zero width in each dimension, so pad the Z
            // dimension a small amount.
            output_box = aabb(Vector3(_x0, _z0, _k - 0.0001), Vector3(_x1, _z1, _k + 0.0001));
            return true;
        }
};

class YZRectangle : public hittable {
    private:
        std::shared_ptr<material> _material;
        double _y0, _y1, _z0, _z1, _k;

    public:
        YZRectangle() {}
        YZRectangle(double y0, double y1, double z0, double z1, double k, std::shared_ptr<material> material):
            _y0(y0), _y1(y1), _z0(z0), _z1(z1), _k(k), _material(material) {};
        
        virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
        virtual bool bounding_box(double time0, double time1, aabb& output_box) override {
            // The bounding box must have non-zero width in each dimension, so pad the Z
            // dimension a small amount.
            output_box = aabb(Vector3(_y0, _z0, _k - 0.0001), Vector3(_y1, _z1, _k + 0.0001));
            return true;
        }
};

#endif