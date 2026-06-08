/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/


#include "Camera.hpp"

namespace Graphics
{
    Camera::Camera(double fov) : _fov(fov)
    {
        this->_position = Maths::Vector3D{0, 0, -10};
        this->_rotation = Maths::Quaternion::fromEulerDegrees(0, 0, 0);
    }

    double Camera::getFov() const
    {
        return this->_fov;
    }

    void Camera::setFov(double fov)
    {
        this->_fov = fov;
    }
} // namespace Graphics