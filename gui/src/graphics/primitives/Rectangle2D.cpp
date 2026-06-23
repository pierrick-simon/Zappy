/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Rectangle2D.hpp"

namespace Graphics {
    void Rectangle2D::draw2D() const
    {
        auto rect(*this);
        rect.SetSize(rect.GetSize() * this->getScale());
        rect.Draw(this->getPosition(), this->getRotation(), this->getColor());
    }

    raylib::Color &Rectangle2D::getColor()
    {
        return this->_color;
    }

    const raylib::Color &Rectangle2D::getColor() const
    {
        return this->_color;
    }
} // namespace Graphics
