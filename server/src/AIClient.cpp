/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AiClient
*/

#include "AIClient.hpp"
#include "AICommunication.hpp"
#include "Connect.hpp"
#include "Environement.hpp"
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
        _inventory.emplace(Info::ResourceName::Food, START_FOOD);
        _inventory.emplace(Info::ResourceName::Linemate, 0);
        _inventory.emplace(Info::ResourceName::Deraumere, 0);
        _inventory.emplace(Info::ResourceName::Sibur, 0);
        _inventory.emplace(Info::ResourceName::Mendiane, 0);
        _inventory.emplace(Info::ResourceName::Phiras, 0);
        _inventory.emplace(Info::ResourceName::Thystame, 0);
        Shared::Connect::send(
            _fd, std::to_string(_env.getConnectNbr(_id)) + "\n");
        Shared::Connect::send(_fd,
            std::to_string(_env.getWidth()) + " " +
                std::to_string(_env.getHeight()) + "\n");
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
            if (!_commands.empty() && !_elevate)
                executeCommand();
        }
        _live -= elapsed;
        if (_live.count() <= 0)
            checkAlive();
        auto timeout = _sleep;
        if (_live < timeout)
            timeout = _live;
        return timeout;
    }

    void AIClient::checkAlive()
    {
        if (_inventory.at(Info::ResourceName::Food) == 0) {
            Shared::Connect::send(_fd, ServerCmd::DEAD.getStr() + "\n");
            Shared::Utils::logMsg(
                _logFile, "Client[" + std::to_string(_id) + "] Die.");
            _alive = false;
        } else {
            _inventory.at(Info::ResourceName::Food)--;
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
        if (startCheckIncantation(command))
            return;
        eggLaying(command);
        auto iter = COMMANDS.find(command);
        if (iter != COMMANDS.end()) {
            _sleep = iter->second._timeLimit;
            _command.emplace(SelectCommand {iter, stream});
        } else {
            _sleep = DEFAULT_SLEEP;
            Shared::Connect::send(_fd, ServerCmd::KO.getStr() + "\n");
            Shared::Utils::logMsg(_logFile,
                "Try executing command " + command + " for client[" +
                    std::to_string(_id) + "](Commmand Not found).");
        }
    }

    bool AIClient::startCheckIncantation(const std::string &name)
    {
        bool value = true;
        if (name != ClientCmd::ICT.getStr())
            value = false;
        else if (!_env.startElevation(_id)) {
            _sleep = DEFAULT_SLEEP;
            Shared::Connect::send(_fd, ServerCmd::KO.getStr() + "\n");
            Shared::Utils::logMsg(_logFile,
                "Try executing command " + name + " for client[" +
                    std::to_string(_id) + "](Start Verifications failed).");
        } else {
            Shared::Connect::send(_fd, ServerCmd::EU.getStr() + "\n");
            Shared::Utils::logMsg(_logFile,
                "Client[" + std::to_string(_id) +
                    "] start the elevation ritual.");
        }
        return value;
    }

    void AIClient::eggLaying(const std::string &name)
    {
        if (name != ClientCmd::FRK.getStr())
            return;
        _env.eggLaying(_id);
    }

    void AIClient::forward(std::istringstream &stream)
    {
        _env.movePlayer(_id);
        Shared::Connect::send(_fd, ServerCmd::OK.getStr() + "\n");
    }

    void AIClient::right(std::istringstream &stream)
    {
        _env.rotatePlayer(_id, Rotate::Right);
        Shared::Connect::send(_fd, ServerCmd::OK.getStr() + "\n");
    }

    void AIClient::left(std::istringstream &stream)
    {
        _env.rotatePlayer(_id, Rotate::Left);
        Shared::Connect::send(_fd, ServerCmd::OK.getStr() + "\n");
    }

    void AIClient::inventory(std::istringstream &stream)
    {
        std::string msg = "[";
        bool first = true;
        for (auto [name, nb] : _inventory) {
            if (!first)
                msg += ",";
            msg += Info::getResourceName(name);
            msg += " " + std::to_string(nb);
            first = false;
        }
        msg += "]\n";
        Shared::Connect::send(_fd, msg);
    }

    void AIClient::connectNbr(std::istringstream &stream)
    {
        Shared::Connect::send(
            _fd, std::to_string(_env.getConnectNbr(_id)) + "\n");
    }

    void AIClient::fork(std::istringstream &stream)
    {
        _env.spawnEgg(_id);
        Shared::Connect::send(_fd, ServerCmd::OK.getStr() + "\n");
    }

    void AIClient::eject(std::istringstream &stream)
    {
        if (_env.eject(_id))
            Shared::Connect::send(_fd, ServerCmd::OK.getStr() + "\n");
        else
            Shared::Connect::send(_fd, ServerCmd::KO.getStr() + "\n");
    }

    void AIClient::set(std::istringstream &stream)
    {
        bool value = true;
        std::string resource;
        stream >> resource;
        try {
            auto type = Info::getResource(resource);
            value = _env.takeResource(_id, type);
        } catch (Info::ResourceNotFoundException &_) {
            value = false;
        }
        if (value)
            Shared::Connect::send(_fd, ServerCmd::OK.getStr() + "\n");
        else
            Shared::Connect::send(_fd, ServerCmd::KO.getStr() + "\n");
    }

    void AIClient::take(std::istringstream &stream)
    {
        bool value = true;
        std::string resource;
        stream >> resource;
        try {
            auto type = Info::getResource(resource);
            auto find = _inventory.find(type);
            if (find != _inventory.end() && find->second != 0) {
                find->second--;
                _env.setResource(_id, type);
            } else
                value = false;
        } catch (Info::ResourceNotFoundException &_) {
            value = false;
        }
        if (value)
            Shared::Connect::send(_fd, ServerCmd::OK.getStr() + "\n");
        else
            Shared::Connect::send(_fd, ServerCmd::KO.getStr() + "\n");
    }

    void AIClient::broadcast(std::istringstream &stream)
    {
        std::string text = stream.str();
        _env.broadcast(_id, text);
        Shared::Connect::send(_fd, ServerCmd::OK.getStr() + "\n");
    }

    const std::unordered_map<std::string, AIClient::Command>
        AIClient::COMMANDS = {
            {ClientCmd::FWD.getStr(),
                Command {&AIClient::forward, std::chrono::seconds(7)}},
            {ClientCmd::RGT.getStr(),
                Command {&AIClient::right, std::chrono::seconds(7)}},
            {ClientCmd::LFT.getStr(),
                Command {&AIClient::left, std::chrono::seconds(7)}},
            {ClientCmd::IVT.getStr(),
                Command {&AIClient::inventory, std::chrono::seconds(1)}},
            {ClientCmd::CNT.getStr(),
                Command {&AIClient::connectNbr, std::chrono::nanoseconds(1)}},
            {ClientCmd::FRK.getStr(),
                Command {&AIClient::fork, std::chrono::seconds(42)}},
            {ClientCmd::EJT.getStr(),
                Command {&AIClient::eject, std::chrono::seconds(7)}},
            {ClientCmd::STO.getStr(),
                Command {&AIClient::set, std::chrono::seconds(7)}},
            {ClientCmd::TKO.getStr(),
                Command {&AIClient::take, std::chrono::seconds(7)}},
            {ClientCmd::BDT.getStr(),
                Command {&AIClient::broadcast, std::chrono::seconds(7)}},
    };
}; // namespace Zappy
