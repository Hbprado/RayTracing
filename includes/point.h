#ifndef POINT_H
#define POINT_H

#include "vector.h"

class Point
{
public:
    double x, y, z;

    // Protótipos de Construtor
    Point();
    Point(double _x, double _y, double _z);

    // Operações básicas com sobrecarga dos operadores
    bool operator>(const Point &other) const;
    bool operator<(const Point &other) const;
    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
    double distance(const Point &other) const;
    // Operações entre pontos e vetores
    Vector operator-(const Point &other) const;
    Point &operator+=(const Vector &other);
    Point operator+(const Vector &other) const;
};

#endif
