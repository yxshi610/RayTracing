#include "Vector3.h"

// vec constructor
Vector3::Vector3(double x, double y, double z)
{
    SetVec(x, y, z);
}

// set vec function
void Vector3::SetVec(double a, double b, double c)
{
    x = a;
    y = b;
    z = c;
}

// get vec function
int Vector3::getX() { return x; }
int Vector3::getY() { return y; }
int Vector3::getZ() { return z; }