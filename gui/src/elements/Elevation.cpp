/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Elevation
*/

#include "Elevation.hpp"

namespace Zappy {
    Elevation::Elevation(std::size_t x, std::size_t y, std::size_t level,
        std::vector<std::size_t> players) :
        _x(x), _y(y), _level(level), _players(std::move(players))
    {
    }
} // namespace Zappy
