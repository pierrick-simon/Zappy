/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#include "Environement.hpp"
#include <optional>

namespace Zappy {
    Environement::Environement(
        std::size_t width, std::size_t height, std::size_t freq) :
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
        for (auto egg : _eggs) {
            if (egg.second._x = width && egg.second._y)
                info._eggs.push_back({egg.first, egg.second._team});
        }
        for (auto player : _players) {
            if (player.second._x = width && player.second._y)
                info._players.push_back({player.first, player.second._team});
        }
        return info;
    }

    std::size_t Environement::circularMove(
        std::size_t pos, int delta, std::size_t size)
    {
        return static_cast<std::size_t>(
            (static_cast<int>(pos) + delta % static_cast<int>(size) +
                static_cast<int>(size)) %
            static_cast<int>(size));
    }

    void Environement::movePlayer(std::size_t id, Direction dir)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            return;
        auto &player = find->second;
        auto [dx, dy] = _directions.at(dir);
        player._x = circularMove(player._x, dx, _width);
        player._y = circularMove(player._y, dy, _height);
        player._dir = dir;
    }

    Direction Environement::getOpositeDir(Direction dir)
    {
        Direction value = Direction::North;
        if (dir == Direction::North)
            value = Direction::South;
        if (dir == Direction::East)
            value = Direction::West;
        if (dir == Direction::West)
            value = Direction::East;
        return value;
    }

    const std::unordered_map<ResourceName, Environement::Resource>
        Environement::_resources = {
            {ResourceName::Food, {0.5, "food"}},
            {ResourceName::Linemate, {0.3, "linemate"}},
            {ResourceName::Deraumere, {0.15, "deraumere"}},
            {ResourceName::Sibur, {0.1, "sibur"}},
            {ResourceName::Mendiane, {0.1, "mendiane"}},
            {ResourceName::Phiras, {0.08, "phiras"}},
            {ResourceName::Thystame, {0.05, "thystame"}},
    };

    const std::map<Direction, std::pair<int, int>> Environement::_directions = {
        {Direction::North, {0, -1}},
        {Direction::East, {1, 0}},
        {Direction::South, {0, 1}},
        {Direction::West, {-1, 0}}};
}; // namespace Zappy
