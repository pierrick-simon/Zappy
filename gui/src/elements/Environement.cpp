/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#include "Environement.hpp"
#include "Utils.hpp"

namespace Zappy {
    Environement::Environement(int port, const std::string &ip,
        std::ofstream &logFile, bool &isConnect) :
        _connect(port, ip),
        _logFile(logFile),
        _isConnect(isConnect),
        _timeUnit(0)
    {
        _isConnect = false;
    }

    bool Environement::update()
    {
        bool connected = true;
        auto info = _connect.infoToRead(0);
        if (!info.empty() && !infoToRead())
            connected = false;
        else {
            if (!_isConnect)
                connected = connect();
            else
                handleEvents();
        }
        return connected;
    }

    bool Environement::connect()
    {
        bool value = true;

        if (!_events.empty()) {
            if (_events.front() == WELCOME) {
                _events.pop();
                Shared::Connect::send(
                    _connect.getFd(), std::string(TEAM) + "\n");
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

    bool Environement::infoToRead()
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
                _events.push(*line);
            line = Shared::Utils::parseLine(_buffer);
        }
        return true;
    }

    void Environement::handleEvents()
    {
        while (!_events.empty()) {
            std::istringstream stream(_events.front());
            std::string event;
            stream >> event;
            _events.pop();
            if (stream.fail())
                return;
            auto iter = EVENTS.find(event);
            if (iter != EVENTS.end()) {
                iter->second(*this, stream);
                Shared::Utils::logMsg(_logFile,
                    "Recieved event " + iter->first + " from server.");
            } else {
                Shared::Utils::logMsg(
                    _logFile, "Event " + event + " not handle yet.");
            }
        }
    }

    const std::unordered_map<std::string, Environement::Event>
        Environement::EVENTS = {

    };
} // namespace Zappy
