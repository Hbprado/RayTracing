#include "camera.h"
#include "sphere.h"
#include "plane.h"
#include "mesh.h"
#include "vector.h"
#include "point.h"
#include "ray.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

void saveImage(const std::string &filename, const std::vector<std::vector<Vector>> &image, int width, int height)
{
    std::ofstream file(filename);
    file << "P3\n"
         << width << " " << height << "\n255\n";
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            file << static_cast<int>(image[y][x].x * 255) << " "
                 << static_cast<int>(image[y][x].y * 255) << " "
                 << static_cast<int>(image[y][x].z * 255) << " ";
        }
        file << "\n";
    }
    file.close();
}

void render(const Camera &camera, const std::vector<Object *> &objects, const Mesh &mesh, int width, int height)
{
    std::vector<std::vector<Vector>> image(height, std::vector<Vector>(width, Vector()));
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            double u = static_cast<double>(x) / width;
            double v = static_cast<double>(y) / height;
            Vector rayDirection = camera.getU() * (2 * u - 1) + camera.getV() * (1 - 2 * v) + camera.getW();
            Ray ray(camera.getPosition(), rayDirection.normalize());
            double t_min = std::numeric_limits<double>::max();
            Vector pixel_color(0.0, 0.0, 0.0);

            for (const auto &object : objects)
            {
                double t;
                if (object->intersect(ray.getOrigin(), ray.getDirection(), t) && t < t_min)
                {
                    t_min = t;
                    pixel_color = object->getColor();
                }
            }

            // Interseção com a malha de triângulos
            float t = std::numeric_limits<float>::max();
            Vector color(0.0, 0.0, 0.0);
            if (mesh.intersect(Vector(ray.getOrigin().x, ray.getOrigin().y, ray.getOrigin().z), ray.getDirection(), t, color) && t < t_min)
            {
                t_min = t;
                pixel_color = color;
            }

            image[y][x] = pixel_color;
        }
    }
    saveImage("output.ppm", image, width, height);
}

int main()
{
    // Ajustar a posição da câmera e aumentar o campo de visão
    Camera myCamera(Point(0.0, 0.0, 5.0), Point(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), 2.0, 2, 2); // Aumentar o campo de visão
    Sphere mySphere1(Point(2.0, 0.0, 0.0), 1.0, Vector(1.0, 0.0, 1.0));
    Sphere mySphere2(Point(-1.0, 0.0, 0.0), 1.0, Vector(0.0, 1.0, 0.0));                                                              // Posicionada na frente da mySphere1
    Plane myPlane(Point(0.0, -1.0, 0.0), Vector(0.0, 1.0, 0.0), Vector(1.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0), Vector(1.0, 1.0, 1.0)); // Plano branco

    std::vector<Object *> objects;
    objects.push_back(&mySphere1);
    objects.push_back(&mySphere2);
    objects.push_back(&myPlane);

    // Definir alguns triângulos para a malha e posicioná-los de forma que fiquem visíveis na câmera
    std::vector<Triangle> triangles = {
        Triangle(Vector(0, 2, 10), Vector(-2, -2, 10), Vector(2, -2, 10), Vector(1, 0, 0)), // vermelho
        Triangle(Vector(3, 2, 12), Vector(1, -2, 12), Vector(5, -2, 12), Vector(0, 1, 0))   // verde
    };

    // Criar a malha
    Mesh mesh(triangles);

    render(myCamera, objects, mesh, 600, 600);

    return 0;
}
