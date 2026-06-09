/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#include "Environement.hpp"
#include <algorithm>
#include <ctime>
#include <optional>
#include <random>
#include "ServerException.hpp"
#include "Utils.hpp"

namespace Zappy {
    Environement::Environement(std::size_t width, std::size_t height,
        std::size_t freq, std::ofstream &logFile) :
        _width(width),
        _height(height),
        _freq(freq),
        _tiles(width * height),
        _logFile(logFile)
    {
        std::srand(std::time(nullptr));
    }

    void Environement::addPlayer(
        std::size_t id, const std::string &team, std::size_t _remainingPlace)
    {
        std::size_t nb = std::rand() % _remainingPlace;

        for (auto iter = _eggs.begin(); iter != _eggs.end(); iter++) {
            const auto &egg = iter->second;
            if (egg._team != team)
                continue;
            if (nb != 0) {
                nb--;
                continue;
            }
            auto item = _directions.begin();
            std::advance(item, std::rand() % _directions.size());
            _players.emplace(id, Player {team, item->first, 1, egg._x, egg._y});
            _eggs.erase(iter);
            Shared::Utils::logMsg(_logFile,
                "Client[" + std::to_string(id) + "] spawned in (" +
                    std::to_string(egg._x) + "," + std::to_string(egg._y) +
                    "), looking " + _directions.at(item->first)._str + ".");
            return;
        }
        throw PlayerNotFoundException(id);
    }

    void Environement::removePlayer(std::size_t id)
    {
        auto find = _players.find(id);
        if (find != _players.end())
            _players.erase(find);
    }

    TileInfo Environement::getTileInfo(
        std::size_t width, std::size_t height) const
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
            throw PlayerNotFoundException(id);
        auto &player = find->second;
        auto [dx, dy, _] = _directions.at(dir);
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

    bool Environement::takeResource(std::size_t id, ResourceName name)
    {
        bool value = false;
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        auto tile = _width * find->second._y + find->second._x;
        auto resource = _tiles[tile].find(name);
        if (resource != _tiles[tile].end() && resource->second > 0) {
            value = true;
            resource->second--;
        }
        return value;
    }

    void Environement::setResource(std::size_t id, ResourceName name)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        auto tile = _width * find->second._y + find->second._x;
        auto resource = _tiles[tile].find(name);
        if (resource != _tiles[tile].end())
            resource->second++;
        else
            _tiles[tile].emplace(name, 1);
    }

    std::vector<std::size_t> Environement::checkElevation(
        std::size_t x, std::size_t y, std::size_t level)
    {
        auto tile = _width * y + x;
        auto elevation = _elevations.at(level);
        bool value = true;
        for (auto [name, nb] : elevation._resources) {
            auto isHere = _tiles[tile].find(name);
            if (isHere != _tiles[tile].end() && isHere->second >= nb)
                continue;
            value = false;
            break;
        }
        std::vector<std::size_t> check;
        for (const auto &[id, player] : _players) {
            if (value == false)
                break;
            if (player._level == level && player._x == x && player._y == y)
                check.emplace_back(id);
        }
        if (check.size() < elevation._nbPlayer)
            check.clear();
        return check;
    }

    bool Environement::successElevation(std::size_t x, std::size_t y,
        const Elevation &elevation, const std::vector<size_t> &players)
    {
        bool value = true;
        auto tile = _width * y + x;
        if (players.size() < elevation._nbPlayer)
            value = false;
        for (auto [name, nb] : elevation._resources) {
            auto isHere = _tiles[tile].find(name);
            isHere->second - nb;
        }
        for (auto player : players) {
            auto find = _players.find(player);
            if (find != _players.end())
                find->second._level++;
        }
    }

    std::vector<std::size_t> Environement::startElevation(std::size_t id)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        return checkElevation(
            find->second._x, find->second._y, find->second._level);
    }

    std::vector<std::size_t> Environement::endElevation(
        std::size_t id, std::vector<std::size_t> start)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        auto end = checkElevation(
            find->second._x, find->second._y, find->second._level);
        start.erase(std::remove_if(start.begin(),
                        start.end(),
                        [&end](std::size_t x) {
                            return std::find(end.begin(), end.end(), x) ==
                                end.end();
                        }),
            start.end());
        const auto &elevation = _elevations.at(find->second._level);
        if (start.size() < elevation._nbPlayer)
            start.clear();
        else
            successElevation(
                find->second._x, find->second._y, elevation, start);
        return start;
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

    const std::map<Direction, Environement::Dir> Environement::_directions = {
        {Direction::North, {0, -1, "North"}},
        {Direction::East, {1, 0, "East"}},
        {Direction::South, {0, 1, "South"}},
        {Direction::West, {-1, 0, "West"}}};

    const std::unordered_map<std::size_t, Environement::Elevation>
        Environement::_elevations = {
            {1, {1, {{ResourceName::Linemate, 1}}}},
            {2,
                {2,
                    {{ResourceName::Linemate, 1},
                        {ResourceName::Deraumere, 1},
                        {ResourceName::Sibur, 1}}}},
            {3,
                {2,
                    {{ResourceName::Linemate, 2},
                        {ResourceName::Phiras, 2},
                        {ResourceName::Sibur, 1}}}},
            {4,
                {4,
                    {{ResourceName::Linemate, 1},
                        {ResourceName::Deraumere, 1},
                        {ResourceName::Sibur, 2},
                        {ResourceName::Phiras, 2}}}},
            {5,
                {4,
                    {{ResourceName::Linemate, 1},
                        {ResourceName::Deraumere, 2},
                        {ResourceName::Sibur, 1},
                        {ResourceName::Mendiane, 3}}}},
            {6,
                {6,
                    {{ResourceName::Linemate, 1},
                        {ResourceName::Deraumere, 2},
                        {ResourceName::Sibur, 3},
                        {ResourceName::Phiras, 1}}}},
            {7,
                {6,
                    {{ResourceName::Linemate, 2},
                        {ResourceName::Deraumere, 2},
                        {ResourceName::Sibur, 2},
                        {ResourceName::Mendiane, 2},
                        {ResourceName::Phiras, 2},
                        {ResourceName::Thystame, 1}}}},
    };
}; // namespace Zappy
