/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Camera.hpp"

#include "RayMath.hpp"

namespace Graphics {
    Camera::Camera(float fov) :
        Camera3D {}
    {
        this->fovy = fov;
        this->projection = RayLib::CAMERA_PERSPECTIVE;
        this->up = RayMath::Vector3UnitZ;
    }
} // namespace Graphics
