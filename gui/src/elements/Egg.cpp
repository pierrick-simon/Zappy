/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"

namespace Zappy {
    Egg::Egg(std::size_t x, std::size_t y, std::string team, std::ofstream &logFile) :
        _x(x), _y(y), _team(std::move(team)), _logFile(logFile)
    {
    }
} // namespace Zappy
