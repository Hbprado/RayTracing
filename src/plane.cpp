#include "../includes/plane.h"
#include <cmath>

Plane::Plane(const Point &point, const Vector &normal, const Vector &u, const Vector &v, const Vector &color)
    : point(point), normal(normal.normalize()), u(u.normalize()), v(v.normalize()), color(color) {}

bool Plane::intersect(const Point &rayOrigin, const Vector &rayDirection, double &t) const
{
    double denominator = rayDirection.dot(normal);

    if (std::abs(denominator) > 1e-6)
    {
        Vector toPlane = point - rayOrigin;
        t = toPlane.dot(normal) / denominator;

        return t > 0;
    }

    return false;
}

Vector Plane::getColor() const
{
    return color;
}