/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Model.hpp"

namespace Graphics {
    void Model::draw() const
    {
        auto [axis, angle] = this->getRotation().ToAxisAngle();
        this->Draw(this->getPosition(), axis, angle, this->getScale());
    }
} // namespace Graphics
