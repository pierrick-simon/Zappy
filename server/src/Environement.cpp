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
#include "AIClient.hpp"
#include "AICommunication.hpp"
#include "GUIClient.hpp"
#include "Server.hpp"
#include "ServerException.hpp"
#include "Utils.hpp"

namespace ServerCmd = Shared::AICommunication::Server;

namespace Zappy {
    Environement::Environement(std::size_t width, std::size_t height,
        std::ofstream &logFile, Clients &clients,
        std::unordered_map<std::string, std::size_t> &teams) :
        _width(width),
        _height(height),
        _sleep(SLEEP),
        _tiles(width * height),
        _logFile(logFile),
        _clients(clients),
        _teams(teams)
    {
        std::srand(std::time(nullptr));
        for (auto tile : _tiles) {
            tile.emplace(ResourceName::Food, 0);
            tile.emplace(ResourceName::Linemate, 0);
            tile.emplace(ResourceName::Deraumere, 0);
            tile.emplace(ResourceName::Sibur, 0);
            tile.emplace(ResourceName::Mendiane, 0);
            tile.emplace(ResourceName::Phiras, 0);
            tile.emplace(ResourceName::Thystame, 0);
        }
    }

    std::chrono::nanoseconds Environement::update(
        std::chrono::nanoseconds elapsed)
    {
        _sleep -= elapsed;
        auto min = _sleep;
        if (_sleep.count() <= 0) {
            _sleep = SLEEP;
        }
        for (auto iter = _elevates.begin(); iter != _elevates.end(); iter++) {
            iter->sleep -= elapsed;
            if (iter->sleep.count() <= 0) {
                endElevation(iter->x, iter->y, iter->level, iter->players);
                _elevates.erase(iter);
            }
            if (min > iter->sleep)
                min = iter->sleep;
        }
        return min;
    }

    void Environement::addPlayer(
        std::size_t id, const std::string &team, std::size_t _remainingPlace)
    {
        std::size_t nb = std::rand() % _remainingPlace;

        for (auto iter = _eggs.begin(); iter != _eggs.end(); iter++) {
            const auto &egg = iter->second;
            if (egg.team != team)
                continue;
            if (nb != 0) {
                nb--;
                continue;
            }
            auto item = _directions.begin();
            std::advance(item, std::rand() % _directions.size());
            _players.emplace(
                id, Player {team, item->first, 1, false, egg.x, egg.y});
            Shared::Utils::logMsg(_logFile,
                "Client[" + std::to_string(id) + "] spawned in (" +
                    std::to_string(egg.x) + "," + std::to_string(egg.y) +
                    "), looking " + _directions.at(item->first).str + ".");
            for (auto &[_, client] : _clients.gui)
                client.newPlayerEvent(id, egg.x, egg.y, item->second.nb, team);
            _eggs.erase(iter);
            return;
        }
        throw EggNotFoundException();
    }

    void Environement::removePlayer(
        std::unordered_map<int, AIClient>::iterator iter)
    {
        auto find = _players.find(iter->second.getId());
        auto tile = _width * find->second.y + find->second.x;
        if (find != _players.end()) {
            for (auto [name, nb] : iter->second.getInventory())
                setResource(tile, name, nb);
            _players.erase(find);
        }
    }

    void Environement::spawnEgg(std::size_t id)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        _eggs.emplace(
            _eggId, Egg {find->second.team, find->second.x, find->second.y});
        _teams.at(find->second.team)++;
        _eggId++;
    }

    void Environement::spawnEgg(const std::string &team)
    {
        _eggs.emplace(
            _eggId, Egg {team, std::rand() % _width, std::rand() % _height});
        _eggId++;
    }

    TileInfo Environement::getTileInfo(
        std::size_t width, std::size_t height) const
    {
        width %= _width;
        height %= _height;
        TileInfo info;
        auto tile = _width * height + width;
        info.resources = _tiles[tile];
        for (const auto &egg : _eggs) {
            if (egg.second.x == width && egg.second.y)
                info.eggs.push_back({egg.first, egg.second.team});
        }
        for (const auto &player : _players) {
            if (player.second.x == width && player.second.y)
                info.players.push_back({player.first, player.second.team});
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

    void Environement::movePlayer(std::size_t id)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        auto &player = find->second;
        const auto &dir = _directions.at(find->second.dir);
        player.x = circularMove(player.x, dir.x, _width);
        player.y = circularMove(player.y, dir.y, _height);
        for (auto &[_, client] : _clients.gui)
            client.playerPositionEvent(
                id, player.x, player.y, _directions.at(player.dir).nb);
    }

    void Environement::rotatePlayer(std::size_t id, Rotate rotate)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        auto &player = find->second;
        auto dir = _directions.find(player.dir);
        if (rotate == Rotate::Left) {
            if (dir == _directions.begin())
                player.dir = _directions.end()--->first;
            else
                player.dir = dir--->first;
        } else {
            if (dir == _directions.end()--)
                player.dir = _directions.begin()->first;
            else
                player.dir = dir++->first;
        }
        for (auto &[_, client] : _clients.gui)
            client.playerPositionEvent(
                id, player.x, player.y, _directions.at(player.dir).nb);
    }

    bool Environement::takeResource(std::size_t id, ResourceName name)
    {
        bool value = false;
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        auto tile = _width * find->second.y + find->second.x;
        auto resource = _tiles[tile].find(name);
        if (resource != _tiles[tile].end() && resource->second > 0) {
            value = true;
            resource->second--;
            for (auto &[_, client] : _clients.gui)
                client.tileInfoEvent(
                    find->second.x, find->second.y, _tiles[tile]);
        }
        return value;
    }

    void Environement::setResource(std::size_t id, ResourceName name)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        auto tile = _width * find->second.y + find->second.x;
        auto resource = _tiles[tile].find(name);
        if (resource != _tiles[tile].end())
            resource->second++;
        else
            _tiles[tile].emplace(name, 1);
        for (auto &[_, client] : _clients.gui)
            client.tileInfoEvent(find->second.x, find->second.y, _tiles[tile]);
    }

    void Environement::setResource(
        std::size_t tile, ResourceName name, std::size_t nb)
    {
        auto resource = _tiles[tile].find(name);
        if (resource != _tiles[tile].end())
            resource->second += nb;
        else
            _tiles[tile].emplace(name, nb);
        for (auto &[_, client] : _clients.gui)
            client.tileInfoEvent(tile % _width, tile / _width, _tiles[tile]);
    }

    std::vector<std::size_t> Environement::checkElevation(
        std::size_t x, std::size_t y, std::size_t level, bool elevated)
    {
        auto tile = _width * y + x;
        auto elevation = _elevations.at(level);
        bool value = true;
        for (auto [name, nb] : elevation.resources) {
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
            if (player.elevation == elevated && player.level == level &&
                player.x == x && player.y == y)
                check.emplace_back(id);
        }
        if (check.size() < elevation.nbPlayer)
            check.clear();
        return check;
    }

    void Environement::successElevation(std::size_t x, std::size_t y,
        const Elevation &elevation, const std::vector<size_t> &players)
    {
        auto tile = _width * y + x;
        for (auto [name, nb] : elevation.resources) {
            auto isHere = _tiles[tile].find(name);
            isHere->second -= nb;
        }
        for (auto player : players) {
            auto find = _players.find(player);
            if (find != _players.end()) {
                find->second.level++;
                find->second.elevation = false;
                setPlayerElevate(player, false);
                Shared::Connect::send(getPlayerFd(player),
                    ServerCmd::CL.getStr() + ": " +
                        std::to_string(find->second.level) + "\n");
                Shared::Utils::logMsg(_logFile,
                    "Client[" + std::to_string(player) + "]: raise to level " +
                        std::to_string(find->second.level) + ".");
            }
        }
        for (auto &[_, client] : _clients.gui)
            client.tileInfoEvent(x, y, _tiles[tile]);
    }

    void Environement::failElevation(const std::vector<size_t> &players)
    {
        for (auto id : players) {
            auto find = _players.find(id);
            if (find != _players.end()) {
                setPlayerElevate(id, false);
                Shared::Utils::logMsg(_logFile,
                    "Client[" + std::to_string(id) +
                        "]: the elevation ritual fail.");
            }
        }
    }

    bool Environement::startElevation(std::size_t id)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        auto list = checkElevation(
            find->second.x, find->second.y, find->second.level, false);
        for (auto player : list) {
            _players.at(player).elevation = true;
            setPlayerElevate(player, true);
        }
        bool value = true;
        if (list.empty())
            value = false;
        else
            _elevates.emplace_back(Elevate {ELEVATE,
                find->second.x,
                find->second.y,
                find->second.level,
                list});
        return value;
    }

    void Environement::endElevation(std::size_t x, std::size_t y,
        std::size_t level, std::vector<std::size_t> start)
    {
        auto end = checkElevation(x, y, level, true);
        if (end.empty())
            failElevation(start);
        else {
            start.erase(std::remove_if(start.begin(),
                            start.end(),
                            [&end](std::size_t x) {
                                return std::find(end.begin(), end.end(), x) ==
                                    end.end();
                            }),
                start.end());
            const auto &elevation = _elevations.at(level);
            if (start.size() >= elevation.nbPlayer)
                successElevation(x, y, elevation, start);
            else
                failElevation(start);
        }
    }

    void Environement::handleEjectPlayer(PlayerIter iter, Direction dir)
    {
        auto [dx, dy, _, _] = _directions.at(dir);
        iter->second.x = circularMove(iter->second.x, dx, _width);
        iter->second.y = circularMove(iter->second.y, dy, _height);
        Shared::Connect::send(getPlayerFd(iter->first),
            ServerCmd::EJT.getStr() + ": " + _directions.at(dir).str + "\n");
        Shared::Utils::logMsg(_logFile,
            "Client[" + std::to_string(iter->first) + "] been push to the " +
                _directions.at(dir).str + ".");
        for (auto &[_, client] : _clients.gui)
            client.playerExpulsionEvent(iter->first);
    }

    void Environement::handleDestroyEgg(EggIter iter)
    {
        _teams.at(iter->second.team)--;
        for (auto &[_, client] : _clients.gui)
            client.eggDestroyEvent(iter->first);
        _eggs.erase(iter);
    }

    bool Environement::eject(std::size_t id)
    {
        bool status = false;
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        for (auto iter = _players.begin(); iter != _players.end(); iter++) {
            if (find == iter)
                continue;
            if (iter->second.x == find->second.x &&
                iter->second.y == find->second.y) {
                handleEjectPlayer(iter, find->second.dir);
                status = true;
            }
        }
        for (auto iter = _eggs.begin(); iter != _eggs.end(); iter++) {
            if (iter->second.x == find->second.x &&
                iter->second.y == find->second.y) {
                handleDestroyEgg(iter);
                status = true;
            }
        }
        return status;
    }

    std::size_t Environement::getConnectNbr(std::size_t id) const
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        return _teams.at(find->second.team);
    }

    ResourceName Environement::getResource(const std::string &name)
    {
        for (const auto &[type, resource] : _resources) {
            if (resource.str == name)
                return type;
        }
        throw ResourceNotFoundException();
    }

    int Environement::getPlayerFd(std::size_t id)
    {
        for (auto &[fd, client] : _clients.ai) {
            if (client.getId() == id)
                return fd;
        }
        throw PlayerNotFoundException(id);
    }

    void Environement::setPlayerElevate(std::size_t id, bool value)
    {
        for (auto &[fd, client] : _clients.ai) {
            if (client.getId() == id) {
                client.setElevate(value);
            }
        }
        throw PlayerNotFoundException(id);
    }

    PlayerInfo Environement::getPlayerInfo(std::size_t id) const
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        auto player = find->second;
        PlayerInfo info;
        info.x = player.x;
        info.y = player.y;
        info.team = player.team;
        info.level = info.level;
        info.dir = _directions.at(player.dir).nb;
        for (const auto &[_, client] : _clients.ai) {
            if (client.getId() == id) {
                info.inventory = client.getInventory();
                return info;
            }
        }
        throw PlayerNotFoundException(id);
    }

    std::vector<std::string> Environement::getTeamsName() const
    {
        std::vector<std::string> names;
        names.reserve(_teams.size());
        std::transform(_teams.begin(),
            _teams.end(),
            std::back_inserter(names),
            [](const auto &pair) { return pair.first; });
        return names;
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
        {Direction::North, {0, -1, "North", 1}},
        {Direction::East, {1, 0, "East", 2}},
        {Direction::South, {0, 1, "South", 3}},
        {Direction::West, {-1, 0, "West", 4}}};

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
