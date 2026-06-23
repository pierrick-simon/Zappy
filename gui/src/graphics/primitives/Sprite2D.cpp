/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Sprite2D.hpp"

namespace Graphics {
    void Sprite2D::draw2D() const
    {
        const Rectangle src = {0.0f,
            0.0f,
            static_cast<float>(this->GetWidth()),
            static_cast<float>(this->GetHeight())};
        const Rectangle dst = {this->_position.x,
            this->_position.y,
            static_cast<float>(this->GetWidth()) * _scale.x,
            static_cast<float>(this->GetHeight()) * _scale.y};
        this->Draw(src, dst, _origin, _rotation, _color);
    }

    raylib::Color &Sprite2D::getColor()
    {
        return this->_color;
    }

    const raylib::Color &Sprite2D::getColor() const
    {
        return this->_color;
    }

    void Sprite2D::setColor(raylib::Color color)
    {
        _color = color;
    }
} // namespace Graphics
