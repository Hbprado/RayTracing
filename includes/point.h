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

    // Métodos utilizando a sobrecarga dos operadores
    bool operator>(const Point &other) const;
    bool operator<(const Point &other) const;
    bool operator==(const Point &other) const;
    bool operator!=(const Point &other) const;
    double distance(const Point &other) const;
};

#endif
