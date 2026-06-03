/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AiClient
*/

#include "AIClient.hpp"
#include "Utils.hpp"
#include "Connect.hpp"

namespace Zappy {
    AIClient::AIClient(int fd, std::size_t id, std::string team,
        std::ofstream &logFile) :
        _fd(fd), _id(id), _team(team), _logFile(logFile)
    {
        Shared::Utils::logMsg(_logFile, "Cleint[" + std::to_string(id)
            + "] joined the " + _team + " team.");
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
};
