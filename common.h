#ifndef COMMON_H
#define COMMON_H

#include <cstdlib>
#include <cmath>
#include <limits>
#include <memory>

// Constants

const double kInfinity = std::numeric_limits<double>::infinity();
const double kPi = 3.1415926535897932385;

// Utility Functions
inline double RandomDouble() {
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double RandomDouble(double min, double max) {
    // Returns a random real in [min,max).
    return min + (max-min) * RandomDouble();
}

inline int RandomInt(int min, int max) {
    // Returns a random integer in [min,max].
    return static_cast<int>(RandomDouble(min, max+1));
}

inline double DegreesToRadians(double degrees) {
    return degrees * kPi / 180.0;
}

inline double Clamp(double x, double min, double max) {
    if (x < min) return min;
    if (x > max) return max;
    return x;
}

// Common Headers

#include "ray.h"
#include "vector3d.h"

#endif