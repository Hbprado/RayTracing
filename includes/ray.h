#ifndef RAY_H
#define RAY_H

#include "point.h"
#include "vector.h"

class Ray
{
public:
    Ray(const Point &origin, const Vector &direction);

    // Métodos para obter origem e direção do raio
    const Point &getOrigin() const;
    const Vector &getDirection() const;

    // Calcular ponto em uma determinada distância ao longo do raio
    Point getPointAtDistance(double distance) const;

private:
    Point origin;
    Vector direction;
};

#endif