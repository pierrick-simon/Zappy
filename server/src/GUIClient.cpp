/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUIClient
*/

#include "GUIClient.hpp"
#include "Connect.hpp"
#include "Utils.hpp"

namespace Zappy {
    GUIClient::GUIClient(int fd, std::size_t id, std::ofstream &logFile) :
        _fd(fd), _id(id), _logFile(logFile)
    {
        Shared::Utils::logMsg(_logFile,
            "Client[" + std::to_string(id) + "] joined the GRAPHIC team.");
    }

    void GUIClient::infoToRead()
    {
        Shared::Connect::receiveChunk(_fd, _buffer);
        addCommand();
    }

    void GUIClient::addCommand()
    {
        auto line = Shared::Utils::parseLine(_buffer);
        while (line) {
            if (!line->empty())
                _command.push(*line);
            line = Shared::Utils::parseLine(_buffer);
        }
    }
} // namespace Zappy
