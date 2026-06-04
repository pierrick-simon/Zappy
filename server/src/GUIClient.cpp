/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUIClient
*/

#include "GUIClient.hpp"
#include "Connect.hpp"
#include "GUICommunication.hpp"
#include "Utils.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;
namespace ClientCmd = Shared::GUICommunication::Client;

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

    void GUIClient::update()
    {
        if (!_command.empty()) {
            std::istringstream stream(_command.front());
            std::string command;
            stream >> command;
            _command.pop();
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
    }

    const std::unordered_map<std::string, GUIClient::Command>
        GUIClient::COMMANDS = {

    };
} // namespace Zappy
