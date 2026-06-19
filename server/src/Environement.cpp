/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#include "Environement.hpp"
#include <algorithm>
#include <array>
#include <ctime>
#include <optional>
#include <random>
#include <ranges>
#include "AIClient.hpp"
#include "AICommunication.hpp"
#include "GUIClient.hpp"
#include "GUIEvents.hpp"
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
        for (auto &tile : _tiles)
            tile = Info::INIT_RESOUCES;
    }

    std::chrono::milliseconds Environement::update(
        std::chrono::milliseconds elapsed)
    {
        _sleep -= elapsed;
        if (_sleep.count() <= 0) {
            _sleep = SLEEP;
        }
        auto min = _sleep;
        for (auto iter = _elevates.begin(); iter != _elevates.end();) {
            iter->sleep -= elapsed;
            if (iter->sleep.count() <= 0) {
                endElevation(iter->x, iter->y, iter->level, iter->players);
                iter = _elevates.erase(iter);
                continue;
            } else {
                if (min > iter->sleep)
                    min = iter->sleep;
                iter++;
            }
        }
        return min;
    }

    std::string Environement::formatTile(
        std::size_t width, std::size_t height) const
    {
        auto info = getTileInfo(width, height);
        std::string formatedTile;

        for (auto p : info.players)
            formatedTile += "player ";
        for (auto e : info.eggs)
            formatedTile += "egg ";
        for (auto r : info.resources)
            formatedTile += Info::resources.at(r.first).str + " ";
        if (!info.players.empty() || !info.eggs.empty() ||
            !info.resources.empty())
            formatedTile += "\b";
        return formatedTile;
    }

    std::string Environement::lookAround(std::size_t id)
    {
        auto p = _players.at(id);
        const auto &dir = Info::directions.at(p.dir);
        std::string list = "[";
        Shared::Vector2<long> left(
            static_cast<long>(dir.y), static_cast<long>(-dir.x));
        Shared::Vector2<long> right(
            static_cast<long>(-dir.y), static_cast<long>(dir.x));

        for (std::size_t i = 0; i <= p.level; ++i) {
            Shared::Vector2<std::size_t> pos(p.x, p.y);
            pos.x = circularMove(
                pos.x, static_cast<int>((left.x + dir.x) * i), _width);
            pos.y = circularMove(
                pos.y, static_cast<int>((left.y + dir.y) * i), _height);
            for (std::size_t j = 0; j < (i * 2) + 1; ++j) {
                list += formatTile(pos.x, pos.y) + ",";
                pos.x = circularMove(pos.x, static_cast<int>(right.x), _width);
                pos.y = circularMove(pos.y, static_cast<int>(right.y), _height);
            }
        }
        list += "\b]";
        return list;
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
            auto item = Info::directions.begin();
            std::advance(item, std::rand() % Info::directions.size());
            _players.emplace(
                id, Player {team, item->first, 1, false, egg.x, egg.y});
            Shared::Utils::logMsg(_logFile,
                "Client[" + std::to_string(id) + "] spawned in (" +
                    std::to_string(egg.x) + "," + std::to_string(egg.y) +
                    "), looking " + Info::directions.at(item->first).str + ".");
            sendToGUI<Shared::NewPlayerEvent>(
                Shared::NewPlayerEvent::NewPlayer {
                    id, egg.x, egg.y, item->second.nb, 1, team});
            sendToGUI<Shared::EggHatchedEvent>(iter->first);
            _eggs.erase(iter);
            return;
        }
        throw EggNotFoundException();
    }

    void Environement::newGuiInfo(int fd)
    {
        for (const auto &[id, player] : _players) {
            Shared::NewPlayerEvent event(Shared::NewPlayerEvent::NewPlayer {id,
                player.x,
                player.y,
                Info::directions.at(player.dir).nb,
                player.level,
                player.team});
            event.send({fd});
        }
    }

    void Environement::removePlayer(
        std::unordered_map<int, AIClient>::iterator iter)
    {
        auto find = _players.find(iter->second.getId());
        auto tile = _width * find->second.y + find->second.x;
        if (find != _players.end()) {
            for (auto [name, nb] : iter->second.getInventory())
                setResource(tile, name, nb);
            sendToGUI<Shared::PlayerDeathEvent>(find->first);
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
        sendToGUI<Shared::EggLaidEvent>(
            _eggId, id, find->second.x, find->second.y);
        _eggId++;
    }

    void Environement::spawnEgg(const std::string &team)
    {
        _eggs.emplace(
            _eggId, Egg {team, std::rand() % _width, std::rand() % _height});
        _eggId++;
    }

    void Environement::eggLaying(std::size_t id)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        sendToGUI<Shared::EggLayingEvent>(id);
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
            if (egg.second.x == width && egg.second.y == height)
                info.eggs.push_back({egg.first, egg.second.team});
        }
        for (const auto &player : _players) {
            if (player.second.x == width && player.second.y == height)
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
        const auto &dir = Info::directions.at(find->second.dir);
        player.x = circularMove(player.x, dir.x, _width);
        player.y = circularMove(player.y, dir.y, _height);
        sendToGUI<Shared::PlayerPositionEvent>(
            id, player.x, player.y, Info::directions.at(player.dir).nb);
    }

    void Environement::rotatePlayer(std::size_t id, Rotate rotate)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        auto &player = find->second;
        auto dir = Info::directions.find(player.dir);
        if (rotate == Rotate::Left) {
            if (dir == Info::directions.begin())
                player.dir = Info::directions.rbegin()->first;
            else
                player.dir = (--dir)->first;
        } else {
            if (dir == --Info::directions.end())
                player.dir = Info::directions.begin()->first;
            else
                player.dir = (++dir)->first;
        }
        sendToGUI<Shared::PlayerPositionEvent>(
            id, player.x, player.y, Info::directions.at(player.dir).nb);
    }

    bool Environement::takeResource(std::size_t id, Info::ResourceName name)
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
            sendToGUI<Shared::TakeResourceEvent>(
                id, Info::resources.at(name).nb);
            sendToGUI<Shared::TileInfoEvent>(
                find->second.x, find->second.y, getTileValue(tile));
        }
        return value;
    }

    void Environement::setResource(std::size_t id, Info::ResourceName name)
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
        sendToGUI<Shared::SetResourceEvent>(id, Info::resources.at(name).nb);
        sendToGUI<Shared::TileInfoEvent>(
            find->second.x, find->second.y, getTileValue(tile));
    }

    void Environement::setResource(
        std::size_t tile, Info::ResourceName name, std::size_t nb)
    {
        auto resource = _tiles[tile].find(name);
        if (resource != _tiles[tile].end())
            resource->second += nb;
        else
            _tiles[tile].emplace(name, nb);
        sendToGUI<Shared::TileInfoEvent>(
            tile % _width, tile / _width, getTileValue(tile));
    }

    std::vector<std::size_t> Environement::checkElevation(
        std::size_t x, std::size_t y, std::size_t level, bool elevated)
    {
        auto tile = _width * y + x;
        auto elevation = Info::elevations.at(level);
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

    void Environement::checkEnd()
    {
        std::map<std::string, std::size_t> map;
        for (const auto &[_, player] : _players) {
            auto find = map.find(player.team);
            if (find != map.end())
                find->second++;
            else
                map.emplace(player.team, 1);
        }
        auto greatest = map.begin();
        for (auto iter = map.begin(); iter != map.end(); iter++) {
            if (greatest->second < iter->second)
                greatest = iter;
        }
        if (greatest->second >= WIN) {
            _end = true;
            sendToGUI<Shared::EndOfGameEvent>(greatest->first);
            Shared::Utils::logMsg(
                _logFile, "The " + greatest->first + " team won the game.");
        }
    }

    void Environement::successElevation(std::size_t x, std::size_t y,
        const Info::Elevation &elevation, const std::vector<size_t> &players,
        std::size_t level)
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
        sendToGUI<Shared::TileInfoEvent>(x, y, getTileValue(tile));
        if (level + 1 == MAX_LEVEL)
            checkEnd();
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
        else {
            _elevates.emplace_back(Elevate {ELEVATE,
                find->second.x,
                find->second.y,
                find->second.level,
                list});
            sendToGUI<Shared::StartIncantationEvent>(
                find->second.x, find->second.y, find->second.level, list);
        }
        return value;
    }

    void Environement::endElevation(std::size_t x, std::size_t y,
        std::size_t level, std::vector<std::size_t> start)
    {
        bool result = false;
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
            const auto &elevation = Info::elevations.at(level);
            if (start.size() >= elevation.nbPlayer) {
                successElevation(x, y, elevation, start, level);
                result = true;
            } else
                failElevation(start);
        }
        sendToGUI<Shared::EndIncantationEvent>(x, y, result);
    }

    void Environement::handleEjectPlayer(PlayerIter iter, Info::Direction dir)
    {
        const auto &info = Info::directions.at(dir);
        iter->second.x = circularMove(iter->second.x, info.x, _width);
        iter->second.y = circularMove(iter->second.y, info.y, _height);
        Shared::Connect::send(getPlayerFd(iter->first),
            ServerCmd::EJT.getStr() + ": " + Info::directions.at(dir).str +
                "\n");
        Shared::Utils::logMsg(_logFile,
            "Client[" + std::to_string(iter->first) + "] been push to the " +
                Info::directions.at(dir).str + ".");
        sendToGUI<Shared::PlayerExpulsionEvent>(iter->first);
    }

    Environement::EggIter Environement::handleDestroyEgg(EggIter iter)
    {
        _teams.at(iter->second.team)--;
        sendToGUI<Shared::EggDestroyEvent>(iter->first);
        return _eggs.erase(iter);
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
        for (auto iter = _eggs.begin(); iter != _eggs.end();) {
            if (iter->second.x == find->second.x &&
                iter->second.y == find->second.y) {
                iter = handleDestroyEgg(iter);
                status = true;
            } else {
                ++iter;
            }
        }
        return status;
    }

    Shared::Vector2<int> Environement::getBroadCastVector(
        const Player &sender, const Player &receiver) const
    {

        std::array<Shared::Vector2<int>, 9> vectors;
        std::size_t index = 0;
        double minDist = -1;
        std::size_t minIndex = 0;

        for (int j = -1; j <= 1; ++j) {
            for (int i = -1; i <= 1; ++i) {
                vectors[index].x = static_cast<int>(sender.x) -
                    (static_cast<int>(receiver.x) +
                        (i * static_cast<int>(_width)));
                vectors[index].y = static_cast<int>(sender.y) -
                    (static_cast<int>(receiver.y) +
                        (j * static_cast<int>(_height)));
                ++index;
            }
        }
        for (std::size_t i = 0; i < index; ++i) {
            auto norm = vectors[i].norm();
            if (norm < minDist || minDist == -1) {
                minDist = norm;
                minIndex = i;
            }
        }
        return vectors[minIndex];
    }

    std::size_t Environement::getTileNb(
        const Player &receiver, const Shared::Vector2<int> &v)
    {
        if (v.x == 0 && v.y == 0)
            return 0;
        const auto &dir = Info::directions.at(receiver.dir);
        Shared::Vector2<int> dirV(dir.x, dir.y);
        auto angle = dirV.angle(v);
        for (auto chunk : _broadcastChunks) {
            auto lowerAngle = dirV.angle(
                chunk.second.first[static_cast<std::size_t>(receiver.dir)]);
            auto hightAngle = dirV.angle(
                chunk.second.second[static_cast<std::size_t>(receiver.dir)]);
            if (angle <= std::max(lowerAngle, hightAngle) &&
                angle > std::min(lowerAngle, hightAngle))
                return chunk.first;
        }
        throw ServerException("Error getTileNb");
    }

    void Environement::broadcast(std::size_t id, const std::string &text)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        sendToGUI<Shared::BroadcastEvent>(id, text);
        for (auto &p : _players) {
            if (p.first == find->first)
                continue;
            auto v = getBroadCastVector(find->second, p.second);
            auto i = getTileNb(p.second, v);
            Shared::Connect::send(getPlayerFd(p.first),
                ServerCmd::MSG.getStr() + " " + std::to_string(i) + ", " +
                    text + "\n");
        }
    }

    std::size_t Environement::getConnectNbr(std::size_t id) const
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw PlayerNotFoundException(id);
        return _teams.at(find->second.team);
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
                return;
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
        info.level = player.level;
        info.dir = Info::directions.at(player.dir).nb;
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

    std::vector<std::size_t> Environement::getTileValue(std::size_t tile)
    {
        std::vector<std::size_t> value(_tiles[tile].size());
        std::ranges::copy(std::views::values(_tiles[tile]), value.begin());
        return value;
    }

    const std::unordered_map<std::size_t,
        std::pair<Shared::Vector2<double>, Shared::Vector2<double>>>
        Environement::_broadcastChunks = {{1, {{0.0, 1.5}, {-0.5, 1.5}}},
            {2, {{-0.5, 1.5}, {-1.5, 0.5}}},
            {3, {{-1.5, 0.5}, {-1.5, -0.5}}},
            {4, {{-1.5, -0.5}, {-0.5, -1.5}}},
            {5, {{-0.5, -1.5}, {0.5, -1.5}}},
            {6, {{0.5, -1.5}, {1.5, -0.5}}},
            {7, {{1.5, -0.5}, {1.5, 0.5}}},
            {8, {{1.5, 0.5}, {0.5, 1.5}}},
            {1, {{0.5, 1.5}, {0.0, 1.5}}}};

}; // namespace Zappy
