#include "../includes/camera.h"
#include <cmath>
#include <iostream>

Camera::Camera(const Point &position, const Point &lookAt, const Vector &up, double distance, int vResolution, int hResolution)
    : position(position), lookAt(lookAt), up(up), distance(distance), vResolution(vResolution), hResolution(hResolution)
{
    computeUVW();
}

void Camera::setPosition(const Point &newPosition)
{
    position = newPosition;
}

void Camera::setLookAt(const Point &newLookAt)
{
    lookAt = newLookAt;
    computeUVW();
}

void Camera::setUpVector(const Vector &newUp)
{
    up = newUp;
    computeUVW();
}

void Camera::setDistance(double newDistance)
{
    distance = newDistance;
}

void Camera::setResolution(int vRes, int hRes)
{
    vResolution = vRes;
    hResolution = hRes;
}

void Camera::move(const Vector &translation)
{
    position += translation;
    lookAt += translation;
}

// Configurar a câmera para olhar em uma determinada direção
void Camera::lookAtPoint(const Point &target)
{
    lookAt = target;
    computeUVW();
}

// Configurar a distância focal
void Camera::setFocalDistance(double newFocalDistance)
{
    focalDistance = newFocalDistance;
}

// Configurar o campo de visão em graus
void Camera::setFieldOfView(double fov)
{
    fieldOfView = fov;
}

Ray Camera::calculateRayForPixel(int x, int y) const
{
    // Normalizar as coordenadas do pixel
    double ndcX = (x + 0.5) / hResolution;
    double ndcY = (y + 0.5) / vResolution;

    // Converter para coordenadas da tela
    double screenX = 2.0 * ndcX - 1.0;
    double screenY = 1.0 - 2.0 * ndcY;

    // Calcular direção do raio
    Vector rayDirection = w * (-distance) + u * screenX + v * screenY;

    // Ajustar a direção para ser normalizada
    rayDirection = rayDirection.normalize();

    // Criar e retornar o raio
    return Ray(position, rayDirection);
}

// Métodos privados
void Camera::computeUVW()
{
    w = (position - lookAt).normalize();
    u = up.cross(w).normalize();
    v = w.cross(u).normalize();
}