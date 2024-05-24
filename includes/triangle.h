// includes/Triangle.h
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "vector.h"

struct Triangle
{
    Vector v0, v1, v2;
    Vector normal;
    Vector color;

    Triangle(const Vector &v0, const Vector &v1, const Vector &v2, const Vector &color)
        : v0(v0), v1(v1), v2(v2), color(color)
    {
        normal = (v1 - v0).cross(v2 - v0).normalize();
    }
};

#endif
