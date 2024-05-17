#include "../includes/camera.h"
#include "../includes/sphere.h"
#include "../includes/plane.h"
#include "../includes/vector.h"
#include "../includes/point.h"
#include "../includes/ray.h"

#include <iostream>
#include <fstream>
#include <vector>

// Função para salvar a imagem em formato PPM
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

// Função para renderizar a cena
void render(const Camera &camera, const Sphere &sphere1, const Sphere &sphere2, const Plane &plane, int width, int height)
{
    // Buffer de imagem para armazenar as cores dos pixels
    std::vector<std::vector<Vector>> image(height, std::vector<Vector>(width, Vector()));

    // Loop pelos pixels da tela
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            // Calcular a direção do raio para este pixel
            double u = static_cast<double>(x) / width;
            double v = static_cast<double>(y) / height;
            Vector rayDirection = camera.getU() * (2 * u - 1) + camera.getV() * (1 - 2 * v) + camera.getW();

            // Criar um raio da câmera
            Ray ray(camera.getPosition(), rayDirection.normalize());

            // Verificar interseções com esferas e plano
            double tSphere1, tSphere2, tPlane;
            bool hitSphere1 = sphere1.intersect(ray.getOrigin(), ray.getDirection(), tSphere1);
            bool hitSphere2 = sphere2.intersect(ray.getOrigin(), ray.getDirection(), tSphere2);
            bool hitPlane = plane.intersect(ray.getOrigin(), ray.getDirection(), tPlane);

            // Determinar a cor do pixel com base nas interseções
            if ((hitSphere1 && (!hitSphere2 || tSphere1 < tSphere2) && (!hitPlane || tSphere1 < tPlane)) ||
                (hitSphere2 && (!hitSphere1 || tSphere2 < tSphere1) && (!hitPlane || tSphere2 < tPlane)))
            {
                // Escolher a cor da primeira ou segunda esfera com base na interseção mais próxima
                image[y][x] = hitSphere1 ? sphere1.getColor() : sphere2.getColor();
            }
            else
            {
                // Cor de fundo (por exemplo, preto)
                image[y][x] = Vector(0.0, 0.0, 0.0);
            }
        }
    }

    // Salvar a imagem em formato PPM
    saveImage("output.ppm", image, width, height);
}
int main()
{
    // Configurar a câmera, esferas e plano
    Camera myCamera(Point(0.0, 0.0, 5.0), Point(0.0, 0.0, 0.0), Vector(0.0, 1.0, 0.0), 2.0, 2, 2);
    Sphere mySphere1(Point(1.0, 0.0, 0.0), 1.5, Vector(1.0, 0.0, 1.0));
    Sphere mySphere2(Point(2.0, 0.0, 2.5), 1.0, Vector(0.0, 1.0, 0.0)); // Posicionada na frente da mySphere1
    Plane myPlane(Point(0.0, 2.0, 0.0), Vector(0.0, 1.0, 0.0), Vector(1.0, 0.0, 0.0), Vector(0.0, 0.0, 1.0), Vector(1.0, 0.0, 0.0));

    // Renderizar a cena
    render(myCamera, mySphere1, mySphere2, myPlane, 800, 800);

    return 0;
}