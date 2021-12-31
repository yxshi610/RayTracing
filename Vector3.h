#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3
{
private:
    double x;
    double y;
    double z;

public:
    Vector3(double x, double y, double z);
    void SetVec(double x, double y, double z);
    int getX();
    int getY();
    int getZ();
};

#endif