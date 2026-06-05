/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#include "Environement.hpp"

namespace Zappy {
    Environement::Environement(std::size_t width, std::size_t height, std::size_t freq) :
        _width(width), _height(height), _freq(freq), _tiles(width * height)
    {
    }

    TileInfo Environement::getTileInfo(std::size_t width, std::size_t height)
    {
        width %= _width;
        height %= _height;
        TileInfo info;
        auto tile = _width * height + width;
        info._resources = _tiles[tile];
        for (auto egg: _eggs) {
            if (egg.second._x = width && egg.second._y)
                info._eggs.push_back({egg.first, egg.second._team});
        }
        for (auto player: _players) {
            if (player.second._x = width && player.second._y)
                info._players.push_back({player.first, player.second._team});
        }
        return info;
    }

    const std::unordered_map<ResourceName, Environement::Resource> Environement::_resources = {
        {ResourceName::Food, {0.5, "food"}},
        {ResourceName::Linemate, {0.3, "linemate"}},
        {ResourceName::Deraumere, {0.15, "deraumere"}},
        {ResourceName::Sibur, {0.1, "sibur"}},
        {ResourceName::Mendiane, {0.1, "mendiane"}},
        {ResourceName::Phiras, {0.08, "phiras"}},
        {ResourceName::Thystame, {0.05, "thystame"}},
    };
};
