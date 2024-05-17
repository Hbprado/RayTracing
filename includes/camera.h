#ifndef CAMERA_H
#define CAMERA_H

#include "point.h"
#include "vector.h"
#include "ray.h"

class Camera
{
public:
    // Construtor
    Camera(const Point &position, const Point &lookAt, const Vector &up, double distance, int vResolution, int hResolution);

    // Configurar a câmera
    void setPosition(const Point &newPosition);
    void setLookAt(const Point &newLookAt);
    void setUpVector(const Vector &newUp);
    void setDistance(double newDistance);
    void setResolution(int vRes, int hRes);

    // Configurar a câmera para olhar em uma determinada direção
    void lookAtPoint(const Point &target);

    // Configurar a distância focal
    void setFocalDistance(double newFocalDistance);

    // Configurar o campo de visão em graus
    void setFieldOfView(double fov);

    void move(const Vector &translation);

    void printInfo() const;

    // Calcular o raio para um pixel específico na tela (considerando perspectiva)
    Ray calculateRayForPixel(int x, int y) const;

    Point getPosition() const { return position; }
    Point getLookAt() const { return lookAt; }
    Vector getUp() const { return up; }
    Vector getU() const { return u; }
    Vector getV() const { return v; }
    Vector getW() const { return w; }
    double getDistance() const { return distance; }
    int getVResolution() const { return vResolution; }
    int getHResolution() const { return hResolution; }
    double getFocalDistance() const { return focalDistance; }
    double getFieldOfView() const { return fieldOfView; }

private:
    // Métodos privados para calcular os vetores ortonormais U, V, W
    void computeUVW();

    // Atributos
    Point position; // Ponto C
    Point lookAt;   // Ponto M
    Vector up;      // Vetor Vup

    Vector u, v, w;  // Vetores ortonormais U, V, W
    double distance; // Distância entre a câmera e a tela
    int vResolution; // Altura da tela
    int hResolution; // Largura da tela

    double focalDistance; // Distância focal
    double fieldOfView;   // Campo de visão em graus
};
#endif