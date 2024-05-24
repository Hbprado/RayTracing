#ifndef OBJECT_H
#define OBJECT_H

#include "point.h"
#include "vector.h"

class Object
{
public:
    virtual bool intersect(const Point &origin, const Vector &direction, double &t) const = 0;
    virtual Vector getColor() const = 0;
    virtual ~Object() = default;
};

#endif
