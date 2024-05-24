#ifndef PLANE_H
#define PLANE_H

#include "point.h"
#include "vector.h"
#include "object.h"

class Plane : public Object
{
public:
    Plane(const Point &point, const Vector &normal, const Vector &u, const Vector &v, const Vector &color);

    bool intersect(const Point &rayOrigin, const Vector &rayDirection, double &t) const override;
    Vector getColor() const override;

private:
    Point point;
    Vector normal;
    Vector u, v;
    Vector color;
};

#endif
