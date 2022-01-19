#ifndef SPHERE_H
#define SPHERE_H

#include "../common.h"
#include "hittable.h"

class Sphere : public Hittable {
private:
    Vector3d center_;
    double radius_;
    std::shared_ptr<Material> material_ptr_;
    void GetSphereUV(Vector3d P, double& u, double& v);
            // p: a given point on the Sphere of radius one, centered at the origin.
            // u: returned value [0,1] of angle around the Y axis from X=-1.
            // v: returned value [0,1] of angle from Y=-1 to Y=+1.
    
public:
    Sphere();
    Sphere(Vector3d center, double radius, std::shared_ptr<Material> material_ptr);

    Vector3d center();
    double radius();

    virtual bool hit(Ray r, double t_min, double t_max, hit_record& rec) override;
    bool BoundingBox(double time0, double time1, AABB& output_box);
};

#endif