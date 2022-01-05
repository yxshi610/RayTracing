#ifndef SPHERE_H
#define SPHERE_H

#include "../main.h"
#include "hittable.h"

class sphere : public hittable {
private:
    Vector3 _center;
    double _radius;
    std::shared_ptr<material> _mat_ptr;
    void get_sphere_uv(Vector3 P, double& u, double& v);
            // p: a given point on the sphere of radius one, centered at the origin.
            // u: returned value [0,1] of angle around the Y axis from X=-1.
            // v: returned value [0,1] of angle from Y=-1 to Y=+1.
    
public:
    sphere() {}
    sphere(Vector3 center, double radius, std::shared_ptr<material> m);

    Vector3 center();
    double radius();

    bool hit(Ray r, double t_min, double t_max, hit_record& rec);
    bool bounding_box(double time0, double time1, aabb& output_box);
};

#endif