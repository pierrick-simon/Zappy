/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Text2D.hpp"

namespace Graphics {
    void Text2D::draw() const
    {
        this->Draw(this->getPosition(), this->getRotation());
    }
} // namespace Graphics
