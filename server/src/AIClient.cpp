/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AiClient
*/

#include "AIClient.hpp"
#include "AICommunication.hpp"
#include "Connect.hpp"
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
                _command.value()->second._func(*this);
                Shared::Utils::logMsg(_logFile,
                    "Executed command " + _command.value()->first +
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
            Shared::Connect::send(_fd, ServerCmd::DEAD.getStr());
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
            _command = iter;
        } else {
            _sleep = DEFAULT_SLEEP;
            Shared::Connect::send(_fd, ServerCmd::KO.getStr());
            Shared::Utils::logMsg(_logFile,
                "Try executing command " + command + " for client[" +
                    std::to_string(_id) + "](Commmand Not found).");
        }
    }

    void AIClient::forward(AIClient &client)
    {
        client._env.movePlayer(client._id);
        Shared::Connect::send(client._fd, ServerCmd::OK.getStr());
    }

    const std::unordered_map<std::string, AIClient::Command>
        AIClient::COMMANDS = {
            {ClientCmd::FWD.getStr(),
                Command {forward, std::chrono::seconds(7)}},
    };
}; // namespace Zappy
