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
    AIClient::AIClient(
        int fd, std::size_t id, std::string team, std::ofstream &logFile) :
        _fd(fd), _id(id), _team(std::move(team)), _logFile(logFile), _sleep(0)
    {
        Shared::Utils::logMsg(_logFile,
            "Client[" + std::to_string(id) + "] joined the " + _team +
                " team.");
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
            if (!line->empty() && _command.size() < MAX_QUEUE)
                _command.push(*line);
            line = Shared::Utils::parseLine(_buffer);
        }
    }

    void AIClient::update(std::chrono::nanoseconds elapsed)
    {
        if (_sleep.count() > 0)
            _sleep -= elapsed;
        if (_sleep.count() <= 0 && !_command.empty()) {
            std::istringstream stream(_command.front());
            std::string command;
            stream >> command;
            _command.pop();
            if (stream.fail())
                return Shared::Connect::send(_fd, ServerCmd::KO.getStr());
            auto iter = COMMANDS.find(command);
            if (iter != COMMANDS.end()) {
                _sleep = iter->second._timeLimit;
                iter->second._func(*this);
                Shared::Utils::logMsg(_logFile,
                    "Executed command " + iter->first + " for client[" +
                        std::to_string(_id) + "].");
            } else {
                Shared::Connect::send(_fd, ServerCmd::KO.getStr());
                Shared::Utils::logMsg(_logFile,
                    "Try executing command " + command + " for client[" +
                        std::to_string(_id) + "](Commmand Not found).");
            }
        }
    }

    const std::unordered_map<std::string, AIClient::Command>
        AIClient::COMMANDS = {

    };
}; // namespace Zappy
