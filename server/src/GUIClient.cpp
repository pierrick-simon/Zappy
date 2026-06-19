/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUIClient
*/

#include "GUIClient.hpp"
#include <ranges>
#include "Connect.hpp"
#include "Environement.hpp"
#include "GUICommunication.hpp"
#include "GUIEvents.hpp"
#include "ServerException.hpp"
#include "Utils.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;
namespace ClientCmd = Shared::GUICommunication::Client;

namespace Zappy {
    GUIClient::GUIClient(int fd, std::size_t id, std::ofstream &logFile,
        Environement &env, std::size_t f) :
        _fd(fd), _id(id), _logFile(logFile), _env(env), _f(f)
    {
        Shared::Utils::logMsg(_logFile,
            "Client[" + std::to_string(id) + "] joined the GRAPHIC team.");
        _env.newGuiInfo(_fd);
    }

    void GUIClient::infoToRead()
    {
        Shared::Connect::receiveChunk(_fd, _buffer);
        addCommand();
        while (!_commands.empty())
            update();
    }

    void GUIClient::addCommand()
    {
        auto line = Shared::Utils::parseLine(_buffer);
        while (line) {
            if (!line->empty())
                _commands.push(*line);
            line = Shared::Utils::parseLine(_buffer);
        }
    }

    void GUIClient::update()
    {
        std::istringstream stream(_commands.front());
        std::string command;
        stream >> command;
        _commands.pop();
        if (stream.fail())
            return Shared::Connect::send(_fd, ServerCmd::SUC.getStr());
        auto iter = COMMANDS.find(command);
        if (iter != COMMANDS.end()) {
            iter->second(*this, std::move(stream));
            Shared::Utils::logMsg(_logFile,
                "Executed command " + iter->first + " for client[" +
                    std::to_string(_id) + "].");
        } else {
            Shared::Connect::send(_fd, ServerCmd::SUC.getStr());
            Shared::Utils::logMsg(_logFile,
                "Try executing command " + command + " for client[" +
                    std::to_string(_id) + "](Commmand Not found).");
        }
    }

    std::optional<std::size_t> GUIClient::timeUnitUpdate()
    {
        auto tmp = _requestF;
        _requestF.reset();
        return tmp;
    }

    void GUIClient::mapSize(std::istringstream stream)
    {
        send<Shared::MapSizeEvent>(_env.getWidth(), _env.getHeight());
    }

    void GUIClient::tileInfo(std::istringstream stream)
    {
        std::size_t x;
        std::size_t y;
        stream >> x >> y;
        TileInfo info = _env.getTileInfo(x, y);
        std::vector<std::size_t> resources(info.resources.size());
        std::ranges::copy(
            std::views::values(info.resources), resources.begin());
        send<Shared::TileInfoEvent>(x, y, resources);
    }

    void GUIClient::tilesInfo(std::istringstream stream)
    {
        auto x = _env.getWidth();
        auto y = _env.getHeight();
        for (std::size_t i = 0; i < x; i++) {
            for (std::size_t j = 0; j < y; j++) {
                std::istringstream tmp(
                    std::to_string(i) + " " + std::to_string(j));
                tileInfo(std::move(tmp));
            }
        }
    }

    void GUIClient::teamsName(std::istringstream stream)
    {
        auto names = _env.getTeamsName();
        for (const auto &name : names)
            send<Shared::TeamNameEvent>(name);
    }

    void GUIClient::playerPosition(std::istringstream stream)
    {
        std::size_t id;
        char hash;
        stream >> hash >> id;
        try {
            auto player = _env.getPlayerInfo(id);
            send<Shared::PlayerPositionEvent>(
                id, player.x, player.y, player.dir);
        } catch (PlayerNotFoundException &e) {
        }
    }

    void GUIClient::playerLevel(std::istringstream stream)
    {
        std::size_t id;
        char hash;
        stream >> hash >> id;
        try {
            auto player = _env.getPlayerInfo(id);
            send<Shared::PlayerLevelEvent>(id, player.level);
        } catch (PlayerNotFoundException &e) {
        }
    }

    void GUIClient::playerInventory(std::istringstream stream)
    {
        std::size_t id;
        char hash;
        stream >> hash >> id;
        try {
            auto player = _env.getPlayerInfo(id);
            std::vector<std::size_t> resources(player.inventory.size());
            std::ranges::copy(
                std::views::values(player.inventory), resources.begin());
            send<Shared::PlayerInventoryEvent>(
                id, player.x, player.y, resources);
        } catch (PlayerNotFoundException &e) {
        }
    }

    void GUIClient::getTimeUnit(std::istringstream stream)
    {
        send<Shared::GetTimeUnit>(_f);
    }

    void GUIClient::setTimeUnit(std::istringstream stream)
    {
        std::size_t id = 0;
        stream >> id;
        if (id != 0)
            _requestF = id;
    }

    void GUIClient::timeUnitEvent(std::size_t f)
    {
        _f = f;
        send<Shared::SetTimeUnit>(_f);
    }

    const std::unordered_map<std::string, GUIClient::Command>
        GUIClient::COMMANDS = {
            {ClientCmd::MSZ.getStr(), &GUIClient::mapSize},
            {ClientCmd::BCT.getStr(), &GUIClient::tileInfo},
            {ClientCmd::MCT.getStr(), &GUIClient::tilesInfo},
            {ClientCmd::TNA.getStr(), &GUIClient::teamsName},
            {ClientCmd::PPO.getStr(), &GUIClient::playerPosition},
            {ClientCmd::PLV.getStr(), &GUIClient::playerLevel},
            {ClientCmd::PIN.getStr(), &GUIClient::playerInventory},
            {ClientCmd::SGT.getStr(), &GUIClient::getTimeUnit},
            {ClientCmd::SST.getStr(), &GUIClient::setTimeUnit},
    };
} // namespace Zappy
