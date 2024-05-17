#include "../includes/sphere.h"
#include <cmath>

Sphere::Sphere(const Point &center, double radius, const Vector &color)
    : center(center), radius(radius), color(color) {}

bool Sphere::intersect(const Point &origin, const Vector &direction, double &t) const
{
    Vector oc = origin - center;
    double a = direction.dot(direction);
    double b = 2.0 * oc.dot(direction);
    double c = oc.dot(oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0)
    {
        double root1 = (-b - std::sqrt(discriminant)) / (2.0 * a);
        double root2 = (-b + std::sqrt(discriminant)) / (2.0 * a);

        t = (root1 < root2) ? root1 : root2;

        return true;
    }

    return false;
}

Vector Sphere::getColor() const
{
    return color;
}