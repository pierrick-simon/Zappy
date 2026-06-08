/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/


#include "Camera.hpp"

namespace Graphics
{
    Camera::Camera(sf::RenderWindow &window) : GameObject(window)
    {
        this->_position = Maths::Vector3D{0, 0, -10};
        this->_rotation = Maths::Quaternion::fromEulerDegrees(0, 0, 0);
    }
} // namespace Graphics