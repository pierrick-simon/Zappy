/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Transformable2D.hpp"

namespace Graphics {
    void Transformable2D::setPosition(raylib::Vector2 pos)
    {
        _position = pos;
    }

    void Transformable2D::setRotation(float rotation)
    {
        _rotation = rotation;
    }

    void Transformable2D::setScale(raylib::Vector2 scale)
    {
        _scale = scale;
    }

    void Transformable2D::setOrigin(raylib::Vector2 origin)
    {
        _origin = origin;
    }

    const raylib::Vector2 &Transformable2D::getPosition() const
    {
        return this->_position;
    }

    const float &Transformable2D::getRotation() const
    {
        return this->_rotation;
    }

    const raylib::Vector2 &Transformable2D::getScale() const
    {
        return this->_scale;
    }

    const raylib::Vector2 &Transformable2D::getOrigin() const
    {
        return this->_origin;
    }
} // namespace Graphics
