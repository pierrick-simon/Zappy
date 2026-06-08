/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Camera.hpp"

namespace Graphics {
    Camera::Camera(double fov) :
        _fov(fov)
    {
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
