#include "../common.h"

#include <iostream>
#include <iomanip>
#include <math.h>
#include <stdlib.h>

inline double pdf(const Vector3d& p) {
    return 1 / (4*kPi);
}

int main() {
    int N = 1000000;
    auto sum = 0.0;
    for (int i = 0; i < N; i++) {
        Vector3d d = Vector3d::RandomUnitVector();
        auto cosine_squared = d.z()*d.z();
        sum += cosine_squared / pdf(d);
    }
    std::cout << std::fixed << std::setprecision(12);
    std::cout << "I = " << sum/N << '\n';
}