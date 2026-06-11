/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Cube.hpp"

#include "raylib.hpp"

namespace Graphics {
    void Cube::draw() const
    {
        DrawCubeV(this->getPosition(), this->getScale() * DEFAULT_SIZE, RED);
    }
} // namespace Graphics
