/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUIClient
*/

#include "GUIClient.hpp"
#include "Connect.hpp"
#include "GUICommunication.hpp"
#include "ServerException.hpp"
#include "Utils.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;
namespace ClientCmd = Shared::GUICommunication::Client;

namespace Zappy {
    GUIClient::GUIClient(
        int fd, std::size_t id, std::ofstream &logFile, Environement &env) :
        _fd(fd), _id(id), _logFile(logFile), _env(env)
    {
        Shared::Utils::logMsg(_logFile,
            "Client[" + std::to_string(id) + "] joined the GRAPHIC team.");
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
            iter->second(*this, stream);
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

    void GUIClient::mapSize(std::istringstream &stream)
    {
        auto x = " " + std::to_string(_env.getWidth());
        auto y = " " + std::to_string(_env.getHeight());
        Shared::Connect::send(_fd, ServerCmd::MSZ.getStr() + x + y + "\n");
    }

    void GUIClient::tileInfoEvent(std::size_t x, std::size_t y,
        const std::map<ResourceName, std::size_t> &resources) const
    {
        std::string msg = ServerCmd::BCT.getStr() + " ";
        msg += std::to_string(x) + " " + std::to_string(y);
        for (auto [_, nb] : resources)
            msg += " " + std::to_string(nb);
        msg += "\n";
        Shared::Connect::send(_fd, msg);
    }

    void GUIClient::tileInfo(std::istringstream &stream)
    {
        std::size_t x;
        std::size_t y;
        stream >> x >> y;
        tileInfoEvent(x, y, _env.getTileInfo(x, y).resources);
    }

    void GUIClient::tilesInfo(std::istringstream &stream)
    {
        auto x = _env.getWidth();
        auto y = _env.getHeight();
        for (std::size_t i = 0; i < x; i++) {
            for (std::size_t j = 0; j < y; j++) {
                std::istringstream tmp(
                    std::to_string(x) + " " + std::to_string(y));
                tileInfo(tmp);
            }
        }
    }

    void GUIClient::teamsName(std::istringstream &stream)
    {
        auto names = _env.getTeamsName();
        for (const auto &name : names)
            Shared::Connect::send(
                _fd, ServerCmd::TNA.getStr() + " " + name + "\n");
    }

    void GUIClient::playerPositionEvent(
        std::size_t id, std::size_t x, std::size_t y, std::size_t dir) const
    {
        std::string msg = ServerCmd::PPO.getStr() + " ";
        msg += std::to_string(id) + " ";
        msg += std::to_string(x) + " ";
        msg += std::to_string(y) + " ";
        msg += std::to_string(dir) + "\n";
        Shared::Connect::send(_fd, msg);
    }

    void GUIClient::playerPosition(std::istringstream &stream)
    {
        std::size_t id;
        stream >> id;
        try {
            auto player = _env.getPlayerInfo(id);
            playerPositionEvent(id, player.x, player.y, player.dir);
        } catch (PlayerNotFoundException &e) {
        }
    }

    const std::unordered_map<std::string, GUIClient::Command>
        GUIClient::COMMANDS = {
            {ClientCmd::MSZ.getStr(), &GUIClient::mapSize},
            {ClientCmd::BCT.getStr(), &GUIClient::tileInfo},
            {ClientCmd::MCT.getStr(), &GUIClient::tilesInfo},
            {ClientCmd::TNA.getStr(), &GUIClient::teamsName},
            {ClientCmd::PPO.getStr(), &GUIClient::playerPosition},
    };
} // namespace Zappy
