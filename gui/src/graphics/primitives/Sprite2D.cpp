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
        this->Draw(this->getPosition(),
            this->getRotation(),
            this->getScale().Length());
    }
} // namespace Graphics
