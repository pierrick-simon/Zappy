/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Transformable2D.hpp"

namespace Graphics {
    raylib::Vector2 &Transformable2D::getPosition()
    {
        return this->_position;
    }

    raylib::Quaternion &Transformable2D::getRotation()
    {
        return this->_rotation;
    }

    raylib::Vector2 &Transformable2D::getScale()
    {
        return this->_scale;
    }

    const raylib::Vector2 &Transformable2D::getPosition() const
    {
        return this->_position;
    }

    const raylib::Quaternion &Transformable2D::getRotation() const
    {
        return this->_rotation;
    }

    const raylib::Vector2 &Transformable2D::getScale() const
    {
        return this->_scale;
    }
} // namespace Graphics
