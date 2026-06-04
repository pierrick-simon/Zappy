/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUI
*/

#include "GUI.hpp"
#include "Connect.hpp"
#include "Utils.hpp"

namespace Zappy {
    GUI::GUI(int port, const std::string &ip) :
        _connect(port, ip), _logFile(std::string(LOG_FILE))
    {
        Shared::Utils::logMsg(_logFile, "Client GUI Open.");
    }

    void GUI::run()
    {
        bool loop = true;

        while (loop) {
            auto info = _connect.infoToRead();
            if (!info.empty() && !infoToRead())
                break;
            if (!_isConnect)
                loop = connect();
        }
    }

    bool GUI::infoToRead()
    {
        try {
            Shared::Connect::receiveChunk(_connect.getFd(), _buffer);
        } catch (Shared::Connect::CloseException &_) {
            Shared::Utils::logMsg(
                _logFile, "Client GUI Close (Server Disconnected).");
            return false;
        }
        auto line = Shared::Utils::parseLine(_buffer);
        while (line) {
            if (!line->empty())
                _command.push(*line);
            line = Shared::Utils::parseLine(_buffer);
        }
        return true;
    }

    bool GUI::connect()
    {
        bool value = true;

        if (!_command.empty()) {
            if (_command.front() == "WELCOME") {
                _command.pop();
                Shared::Connect::send(_connect.getFd(), "GRAPHIC\n");
                _isConnect = true;
                Shared::Utils::logMsg(
                    _logFile, "Client GUI connect to the server.");
            } else {
                value = false;
                Shared::Utils::logMsg(
                    _logFile, "Client GUI Close (Wrong Connection Message).");
            }
        }
        return value;
    }
} // namespace Zappy
