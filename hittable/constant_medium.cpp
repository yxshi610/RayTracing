#include "constant_medium.h"

bool ConstantMedium::hit(Ray r, double t_min, double t_max, hit_record& rec) {
    // Print occastional samples when debugging. set enableDebug = true;
    const bool kEnableDebug = false;
    const bool kDebugging = kEnableDebug && random_double() < 0.00001;

    hit_record rec1, rec2;

    if (!boundary_->hit(r, -infinity, infinity, rec1)) return false;
    if (!boundary_->hit(r, rec1.t + 0.0001, infinity, rec2)) return false;
    
    if (kDebugging) std::cerr <<"\nt_min=" << rec1.t <<", t_max=" << rec2.t << '\n';

    if (rec1.t < t_min) rec1.t = t_min;
    if (rec2.t > t_max) rec2.t  =t_max;

    if (rec1.t >= rec2.t) return false;

    if (rec1.t < 0) rec1.t = 0;

    const auto kRayLength = r.direction().length();
    const auto kDistanceInsideBoundary = (rec2.t - rec1.t) * kRayLength;
    const auto kHitDistance = neg_inv_density_ * log(random_double());

    if (kHitDistance > kDistanceInsideBoundary) return false;

    rec.t = rec1.t + kHitDistance / kRayLength;
    rec.point = r.at(rec.t);

    if (kDebugging) {
        std::cerr << "kHitDistance = " <<  kHitDistance << '\n'
                  << "rec.t = " <<  rec.t << '\n'
                  << "rec.point = " <<  rec.point << '\n';
    }

    rec.normal = Vector3(1, 0, 0);  // arbitary
    rec.front_face = true;          // arbitary
    rec.mat_ptr = phase_function_;

    return true;
}