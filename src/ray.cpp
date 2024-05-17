#include "../includes/ray.h"

Ray::Ray(const Point &origin, const Vector &direction) : origin(origin), direction(direction.normalize()) {}

const Point &Ray::getOrigin() const
{
    return origin;
}

const Vector &Ray::getDirection() const
{
    return direction;
}

Point Ray::getPointAtDistance(double distance) const
{
    return origin + direction * distance;
}