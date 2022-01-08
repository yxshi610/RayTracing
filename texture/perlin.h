#ifndef PERLIN_H
#define PERLIN_H

#include "../main.h"

class perlin {
    private:
        static const int point_count = 256;
        Vector3* ranvec;
        int* perm_x;
        int* perm_y;
        int* perm_z;

        static int* perlin_generate_perm();
        static void permute(int* p, int n);
        static double trilinear_interp(double c[2][2][2], double u, double v, double w);
        static double perlin_interp(Vector3 c[2][2][2], double u, double v, double w);

    public:
        perlin();
        ~perlin();
        
        double noise(Vector3 P);
        double turb(Vector3 p, int depth = 7);
};

#endif