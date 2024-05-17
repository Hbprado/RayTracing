#include "../includes/point.h"
#include <cmath>
#include <iostream>

using namespace std;

// Inicializando os construtores
Point::Point() : x(0.0), y(0.0), z(0.0){};
Point::Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

// Distância entre pontos
double Point::distance(const Point &other) const
{
    double dx = x - other.x;
    double dy = y - other.y;
    double dz = z - other.z;
    return std::sqrt(dx * dx + dy * dy + dz * dz);
}

// Operações básicas de pontos através da sobrecarga dos operadores
bool Point::operator>(const Point &other) const
{
    return (x > other.x) && (y > other.y) && (z > other.z);
}

bool Point::operator<(const Point &other) const
{
    return (x < other.x) && (y < other.y) && (z < other.z);
}

bool Point::operator==(const Point &other) const
{
    return (x == other.x) && (y == other.y) && (z == other.z);
}

bool Point::operator!=(const Point &other) const
{
    return !(*this == other);
}

Vector Point::operator-(const Point &other) const
{
    return Vector(x - other.x, y - other.y, z - other.z);
}

Point &Point::operator+=(const Vector &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

Point Point::operator+(const Vector &other) const
{
    return Point(x + other.x, y + other.y, z + other.z);
}