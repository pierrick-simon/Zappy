/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AiClient
*/

#include "AIClient.hpp"
#include "AICommunication.hpp"
#include "Connect.hpp"
#include "ServerException.hpp"
#include "Utils.hpp"

namespace ServerCmd = Shared::AICommunication::Server;
namespace ClientCmd = Shared::AICommunication::Client;

namespace Zappy {
    AIClient::AIClient(int fd, std::size_t id, std::string team,
        std::ofstream &logFile, Environement &env) :
        _fd(fd),
        _id(id),
        _team(std::move(team)),
        _logFile(logFile),
        _sleep(0),
        _live(CYCLE_TO_DIE),
        _env(env)
    {
        Shared::Utils::logMsg(_logFile,
            "Client[" + std::to_string(id) + "] joined the " + _team +
                " team.");
        _inventory.emplace(ResourceName::Food, START_FOOD);
        _inventory.emplace(ResourceName::Linemate, 0);
        _inventory.emplace(ResourceName::Deraumere, 0);
        _inventory.emplace(ResourceName::Sibur, 0);
        _inventory.emplace(ResourceName::Mendiane, 0);
        _inventory.emplace(ResourceName::Phiras, 0);
        _inventory.emplace(ResourceName::Thystame, 0);
    }

    void AIClient::infoToRead()
    {
        Shared::Connect::receiveChunk(_fd, _buffer);
        addCommand();
    }

    void AIClient::addCommand()
    {
        auto line = Shared::Utils::parseLine(_buffer);
        while (line) {
            if (!line->empty() && _commands.size() < MAX_QUEUE)
                _commands.push(*line);
            line = Shared::Utils::parseLine(_buffer);
        }
    }

    std::chrono::nanoseconds AIClient::update(std::chrono::nanoseconds elapsed)
    {
        if (_sleep.count() > 0)
            _sleep -= elapsed;
        if (_sleep.count() <= 0) {
            if (_command) {
                _command.value().iter->second._func(
                    *this, _command.value().stream);
                Shared::Utils::logMsg(_logFile,
                    "Executed command " + _command.value().iter->first +
                        " for client[" + std::to_string(_id) + "].");
                _command.reset();
            }
            if (!_commands.empty())
                executeCommand();
        }
        _live -= elapsed;
        if (_live.count() <= 0)
            checkAlive();
        auto timeout = _sleep;
        if (_live < timeout)
            timeout = _live;
        return _sleep;
    }

    void AIClient::checkAlive()
    {
        if (_inventory.at(ResourceName::Food) == 0) {
            Shared::Connect::send(_fd, ServerCmd::DEAD.getStr() + "\n");
            Shared::Utils::logMsg(
                _logFile, "Client[" + std::to_string(_id) + "] Die.");
            _alive = false;
        } else {
            _inventory.at(ResourceName::Food)--;
            Shared::Utils::logMsg(
                _logFile, "Client[" + std::to_string(_id) + "] eat a food.");
            _live = CYCLE_TO_DIE;
        }
    }

    void AIClient::executeCommand()
    {
        std::istringstream stream(_commands.front());
        std::string command;
        stream >> command;
        _commands.pop();
        auto iter = COMMANDS.find(command);
        if (iter != COMMANDS.end()) {
            _sleep = iter->second._timeLimit;
            _command.emplace(SelectCommand {iter, stream});
            startCheckIncantation(command);
        } else {
            _sleep = DEFAULT_SLEEP;
            Shared::Connect::send(_fd, ServerCmd::KO.getStr() + "\n");
            Shared::Utils::logMsg(_logFile,
                "Try executing command " + command + " for client[" +
                    std::to_string(_id) + "](Commmand Not found).");
        }
    }

    void AIClient::startCheckIncantation(const std::string &name)
    {
        if (name != ClientCmd::ICT.getStr())
            return;
        _elevationPlayers = _env.startElevation(_id);
        if (_elevationPlayers.empty()) {
            _command.reset();
            _sleep = DEFAULT_SLEEP;
            Shared::Connect::send(_fd, ServerCmd::KO.getStr() + "\n");
            Shared::Utils::logMsg(_logFile,
                "Try executing command " + name + " for client[" +
                    std::to_string(_id) + "](Start Verifications failed).");
        }
    }

    void AIClient::forward(AIClient &client, std::istringstream &stream)
    {
        client._env.movePlayer(client._id);
        Shared::Connect::send(client._fd, ServerCmd::OK.getStr() + "\n");
    }

    void AIClient::right(AIClient &client, std::istringstream &stream)
    {
        client._env.rotatePlayer(client._id, Rotate::Right);
        Shared::Connect::send(client._fd, ServerCmd::OK.getStr() + "\n");
    }

    void AIClient::left(AIClient &client, std::istringstream &stream)
    {
        client._env.rotatePlayer(client._id, Rotate::Left);
        Shared::Connect::send(client._fd, ServerCmd::OK.getStr() + "\n");
    }

    void AIClient::inventory(AIClient &client, std::istringstream &stream)
    {
        std::string msg = "[";
        bool first = true;
        for (auto [name, nb] : client._inventory) {
            if (!first)
                msg += ",";
            msg += Environement::getResourceName(name);
            msg += " " + std::to_string(nb);
            first = false;
        }
        msg += "]\n";
        Shared::Connect::send(client._fd, msg);
    }

    void AIClient::connectNbr(AIClient &client, std::istringstream &stream)
    {
        Shared::Connect::send(client._fd,
            std::to_string(client._env.getConnectNbr(client._id)) + "\n");
    }

    void AIClient::fork(AIClient &client, std::istringstream &stream)
    {
        client._env.spawnEgg(client._id);
        Shared::Connect::send(client._fd, ServerCmd::OK.getStr() + "\n");
    }

    void AIClient::eject(AIClient &client, std::istringstream &stream)
    {
        if (client._env.eject(client._id))
            Shared::Connect::send(client._fd, ServerCmd::OK.getStr() + "\n");
        else
            Shared::Connect::send(client._fd, ServerCmd::KO.getStr() + "\n");
    }

    void AIClient::set(AIClient &client, std::istringstream &stream)
    {
        bool value = true;
        std::string resource;
        stream >> resource;
        try {
            auto type = Environement::getResource(resource);
            value = client._env.takeResource(client._id, type);
        } catch (ResourceNotFoundException &_) {
            value = false;
        }
        if (value)
            Shared::Connect::send(client._fd, ServerCmd::OK.getStr() + "\n");
        else
            Shared::Connect::send(client._fd, ServerCmd::KO.getStr() + "\n");
    }

    void AIClient::take(AIClient &client, std::istringstream &stream)
    {
        bool value = true;
        std::string resource;
        stream >> resource;
        try {
            auto type = Environement::getResource(resource);
            auto find = client._inventory.find(type);
            if (find != client._inventory.end() && find->second != 0) {
                find->second--;
                client._env.setResource(client._id, type);
            } else
                value = false;
        } catch (ResourceNotFoundException &_) {
            value = false;
        }
        if (value)
            Shared::Connect::send(client._fd, ServerCmd::OK.getStr() + "\n");
        else
            Shared::Connect::send(client._fd, ServerCmd::KO.getStr() + "\n");
    }

    void AIClient::incantation(AIClient &client, std::istringstream &stream)
    {
        client._env.endElevation(client._id, client._elevationPlayers);
        client._elevationPlayers.clear();
    }

    const std::unordered_map<std::string, AIClient::Command>
        AIClient::COMMANDS = {
            {ClientCmd::FWD.getStr(),
                Command {forward, std::chrono::seconds(7)}},
            {ClientCmd::RGT.getStr(), Command {right, std::chrono::seconds(7)}},
            {ClientCmd::LFT.getStr(), Command {left, std::chrono::seconds(7)}},
            {ClientCmd::IVT.getStr(),
                Command {inventory, std::chrono::seconds(1)}},
            {ClientCmd::CNT.getStr(),
                Command {connectNbr, std::chrono::nanoseconds(1)}},
            {ClientCmd::FRK.getStr(), Command {fork, std::chrono::seconds(42)}},
            {ClientCmd::EJT.getStr(), Command {eject, std::chrono::seconds(7)}},
            {ClientCmd::STO.getStr(), Command {set, std::chrono::seconds(7)}},
            {ClientCmd::TKO.getStr(), Command {take, std::chrono::seconds(7)}},
            {ClientCmd::ICT.getStr(),
                Command {incantation, std::chrono::seconds(300)}},
    };
}; // namespace Zappy
