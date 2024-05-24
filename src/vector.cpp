#include "../includes/vector.h"
#include <cmath>
#include <iostream>

Vector::Vector() : x(0.0), y(0.0), z(0.0) {}

Vector::Vector(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

Vector Vector::operator+(const Vector &other) const
{
    return Vector(x + other.x, y + other.y, z + other.z);
}

Vector Vector::operator-(const Vector &other) const
{
    return Vector(x - other.x, y - other.y, z - other.z);
}

Vector Vector::operator*(double scalar) const
{
    return Vector(x * scalar, y * scalar, z * scalar);
}

Vector Vector::operator+=(const Vector &other)
{
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
}

double Vector::dot(const Vector &other) const
{
    return x * other.x + y * other.y + z * other.z;
}

Vector Vector::cross(const Vector &other) const
{
    return Vector(y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x);
}

double Vector::length() const
{
    return std::sqrt(x * x + y * y + z * z);
}

Vector Vector::normalize() const
{
    double len = length();
    if (len != 0.0)
    {
        return *this * (1.0 / len);
    }
    else
    {
        return Vector();
    }
}