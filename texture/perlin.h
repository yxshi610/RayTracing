#ifndef PERLIN_H
#define PERLIN_H

#include "../common.h"

class Perlin {
    private:
        static const int point_count = 256;
        Vector3d* ranvec;
        int* perm_x;
        int* perm_y;
        int* perm_z;

        static int* PerlinGeneratePerm();
        static void Permute(int* p, int n);
        static double TrilinearInterpolation(double c[2][2][2], double u, double v, double w);
        static double PerlinInterpolation(Vector3d c[2][2][2], double u, double v, double w);

    public:
        Perlin();
        ~Perlin();
        
        double Noise(Vector3d P);
        double Turb(Vector3d p, int depth = 7);
};

#endif