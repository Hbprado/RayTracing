#ifndef SPHERE_H
#define SPHERE_H

#include "point.h"
#include "vector.h"

class Sphere
{
public:
    // Construtor
    Sphere(const Point &center, double radius, const Vector &color);

    // Método para testar a interseção com um raio
    bool intersect(const Point &origin, const Vector &direction, double &t) const;

    // Método para obter a cor da esfera
    Vector getColor() const;

private:
    Point center;
    double radius;
    Vector color;
};

#endif