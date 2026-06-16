/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUI
*/

#include "GUI.hpp"
#include "ArgsParser.hpp"
#include "Connect.hpp"
#include "Utils.hpp"

namespace Zappy {
    GUI::GUI(std::vector<std::string> args) :
        _connect(Parser::ArgsParser::getArg<int>(args, "-p", DEFAULT_PORT),
            Parser::ArgsParser::getArg<std::string>(args, "-h", DEFAULT_HOST.data())),
        _logFile(std::string(LOG_FILE))
    {
        Shared::Utils::logMsg(_logFile, "Client GUI Open.");
    }

    void GUI::run()
    {
        bool connected = true;

        while (Graphics::Window::isRunning() && connected) {
            auto info = _connect.infoToRead();
            if (!info.empty() && !infoToRead())
                break;
            if (!_isConnect)
                connected = connect();
            else
                update();
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

    void GUI::update()
    {
        if (!_command.empty()) {
            std::istringstream stream(_command.front());
            std::string command;
            stream >> command;
            _command.pop();
            if (stream.fail())
                return;
            auto iter = COMMANDS.find(command);
            if (iter != COMMANDS.end()) {
                iter->second(*this, stream);
                Shared::Utils::logMsg(_logFile,
                    "Recieved command " + iter->first + " from server.");
            } else {
                Shared::Utils::logMsg(
                    _logFile, "Command " + command + " not handle yet.");
            }
        }
        this->_window.update();
    }

    const std::unordered_map<std::string, GUI::Command> GUI::COMMANDS = {

    };
} // namespace Zappy
