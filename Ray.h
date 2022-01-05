#ifndef RAY_H
#define RAY_H

class Ray {
private:
    Vector3 _origin;
    Vector3 _direction;
    double _time;

public:
    Ray();
    Ray(Vector3 origin, Vector3 direction, double time = 0.0);
    Vector3 origin();
    Vector3 direction();
    Vector3 at(double t);
    double time();
};

#endif