/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Elevation
*/

#include "Elevation.hpp"
#include <algorithm>

namespace Zappy {
    Elevation::Elevation(std::size_t x, std::size_t y, std::size_t level,
        std::vector<std::size_t> players) :
        _x(x), _y(y), _level(level), _players(std::move(players))
    {
    }

    void Elevation::removePlayer(std::size_t id)
    {
        _players.erase(std::remove_if(_players.begin(),
                           _players.end(),
                           [id](std::size_t i) { return id == i; }),
            _players.end());
    }

    std::size_t Elevation::getTile(std::size_t mapWidth) const
    {
        return _y * mapWidth + _x;
    }
} // namespace Zappy
