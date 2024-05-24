// includes/Mesh.h
#ifndef MESH_H
#define MESH_H

#include <vector>
#include "Triangle.h"

class Mesh
{
public:
    std::vector<Triangle> triangles;

    Mesh(const std::vector<Triangle> &triangles) : triangles(triangles) {}

    bool intersect(const Vector &rayOrigin, const Vector &rayDirection, float &t, Vector &outColor) const
    {
        bool hit = false;
        for (const auto &triangle : triangles)
        {
            float tTemp;
            if (intersectTriangle(rayOrigin, rayDirection, triangle, tTemp))
            {
                if (tTemp < t)
                {
                    t = tTemp;
                    outColor = triangle.color;
                    hit = true;
                }
            }
        }
        return hit;
    }

private:
    bool intersectTriangle(const Vector &rayOrigin, const Vector &rayDirection, const Triangle &triangle, float &t) const
    {
        const float EPSILON = 0.0000001;
        Vector edge1 = triangle.v1 - triangle.v0;
        Vector edge2 = triangle.v2 - triangle.v0;
        Vector h = rayDirection.cross(edge2);
        float a = edge1.dot(h);

        if (a > -EPSILON && a < EPSILON)
            return false;

        float f = 1.0 / a;
        Vector s = rayOrigin - triangle.v0;
        float u = f * (s.dot(h));

        if (u < 0.0 || u > 1.0)
            return false;

        Vector q = s.cross(edge1);
        float v = f * (rayDirection.dot(q));

        if (v < 0.0 || u + v > 1.0)
            return false;

        t = f * (edge2.dot(q));
        return t > EPSILON;
    }
};

#endif
