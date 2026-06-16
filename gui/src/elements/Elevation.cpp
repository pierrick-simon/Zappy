/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Elevation
*/

#include "Elevation.hpp"

namespace Zappy {
    Elevation::Elevation(std::size_t x, std::size_t y, std::size_t level,
        std::map<std::size_t, bool> players) :
        _x(x), _y(y), _level(level), _players(std::move(players))
    {
    }

    void Elevation::end(bool success)
    {
        _finish = true;
        _success = success;
    }

    void Elevation::setFinish(bool finish)
    {
        _finish = finish;
    }
} // namespace Zappy
