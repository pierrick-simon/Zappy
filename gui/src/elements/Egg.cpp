/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"

namespace Zappy {
    Egg::Egg(std::string team) :
        _team(std::move(team))
    {
    }
} // namespace Zappy
