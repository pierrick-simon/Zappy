/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"

namespace Zappy {
    Egg::Egg(std::size_t x, std::size_t y, std::string team) :
        _x(x), _y(y), _team(std::move(team))
    {
    }

    std::size_t Egg::getTile(std::size_t mapWidth) const
    {
        return _y * mapWidth + _x;
    }
} // namespace Zappy
