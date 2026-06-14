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
    GUIClient::GUIClient(int fd, std::size_t id, std::ofstream &logFile,
        Environement &env, std::size_t f) :
        _fd(fd), _id(id), _logFile(logFile), _env(env), _f(f)
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

    std::optional<std::size_t> GUIClient::timeUnitUpdate()
    {
        auto tmp = _requestF;
        _requestF.reset();
        return tmp;
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

    void GUIClient::newPlayerEvent(std::size_t id, std::size_t x, std::size_t y,
        std::size_t dir, const std::string &team) const
    {
        std::string msg = ServerCmd::PNW.getStr() + " ";
        msg += std::to_string(id) + " ";
        msg += std::to_string(x) + " ";
        msg += std::to_string(y) + " ";
        msg += std::to_string(dir) + " ";
        msg += std::to_string(1) + " ";
        msg += team + "\n";
        Shared::Connect::send(_fd, msg);
    }

    void GUIClient::playerLevel(std::istringstream &stream)
    {
        std::size_t id;
        stream >> id;
        try {
            auto player = _env.getPlayerInfo(id);
            std::string msg = ServerCmd::PLV.getStr() + " ";
            msg += std::to_string(id) + " ";
            msg += std::to_string(player.level) + "\n";
            Shared::Connect::send(_fd, msg);
        } catch (PlayerNotFoundException &e) {
        }
    }

    void GUIClient::playerInventory(std::istringstream &stream)
    {
        std::size_t id;
        stream >> id;
        try {
            auto player = _env.getPlayerInfo(id);
            std::string msg = ServerCmd::PIN.getStr() + " ";
            msg += std::to_string(id);
            for (auto [_, nb] : player.inventory)
                msg += " " + std::to_string(nb);
            msg += "\n";
            Shared::Connect::send(_fd, msg);
        } catch (PlayerNotFoundException &e) {
        }
    }

    void GUIClient::getTimeUnit(std::istringstream &stream) const
    {
        Shared::Connect::send(
            _fd, ServerCmd::SGT.getStr() + " " + std::to_string(_f) + "\n");
    }

    void GUIClient::setTimeUnit(std::istringstream &stream)
    {
        std::size_t id = 0;
        stream >> id;
        if (id != 0)
            _requestF = id;
    }

    void GUIClient::timeUnitEvent(std::size_t f)
    {
        _f = f;
        Shared::Connect::send(
            _fd, ServerCmd::SGT.getStr() + " " + std::to_string(_f) + "\n");
    }

    void GUIClient::playerExpulsionEvent(std::size_t id) const
    {
        Shared::Connect::send(
            _fd, ServerCmd::PEX.getStr() + " " + std::to_string(id) + "\n");
    }

    void GUIClient::eggDestroyEvent(std::size_t id) const
    {
        Shared::Connect::send(
            _fd, ServerCmd::EDI.getStr() + " " + std::to_string(id) + "\n");
    }

    void GUIClient::broadcastEvent(
        std::size_t id, const std::string &text) const
    {
        Shared::Connect::send(_fd,
            ServerCmd::EDI.getStr() + " " + std::to_string(id) + " " + text +
                "\n");
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
