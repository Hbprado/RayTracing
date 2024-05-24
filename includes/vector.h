#ifndef VECTOR_H
#define VECTOR_H

class Point;
class Vector
{
public:
    double x, y, z;

    Vector();
    Vector(double _x, double _y, double _z);

    // Operações básicas através da sobrecarga dos operadores
    Vector operator+(const Vector &other) const;
    Vector operator-(const Vector &other) const;
    Vector operator*(double scalar) const;
    Vector operator+=(const Vector &other);
    // Demais operações entre vetores
    double dot(const Vector &other) const;
    Vector cross(const Vector &other) const;
    double length() const;
    Vector normalize() const;
};

#endif