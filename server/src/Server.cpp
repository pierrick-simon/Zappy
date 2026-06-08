/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Server
*/

#include "Server.hpp"
#include <csignal>
#include <iostream>
#include "Utils.hpp"

namespace Zappy {

    bool Server::RECEIVED_SIG_INT = false;

    Server::Server(int port, const std::vector<std::string> &teams,
        std::size_t nbPerTeam) :
        _connect(port), _logFile(std::string(LOG_FILE)), _env(100, 100, 100)
    {
        Shared::Utils::logMsg(_logFile, "Server Open.");
        signal(SIGINT, [](int) { RECEIVED_SIG_INT = true; });
        for (const auto &team : teams)
            _teams.emplace(team, nbPerTeam);
        _clock = std::chrono::steady_clock::now();
    }

    Server::~Server()
    {
        Shared::Utils::logMsg(_logFile, "Server Close.");
    }

    void Server::run()
    {
        while (!RECEIVED_SIG_INT) {
            infoToRead();
            update();
        }
    }

    void Server::infoToRead()
    {
        auto infos = _connect.infoToRead(_timeout);
        if (!infos.empty()) {
            if (infos[0] == _connect.getFd())
                addClient();
            handleClient(infos);
        }
    }

    void Server::update()
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = _clock - now;
        _clock = now;
        _timeout = -1;
        std::vector<int> deads;
        for (auto &[id, ai] : _aiClients) {
            auto tmp = ai.update(elapsed);
            auto timeout =
                int(std::chrono::duration_cast<std::chrono::microseconds>(tmp)
                        .count());
            if (tmp.count() > 0 && (_timeout = -1 || timeout < _timeout))
                _timeout = timeout;
            if (!ai.isAlive())
                deads.push_back(id);
        }
        handleDeadClient(deads);
    }

    void Server::handleDeadClient(const std::vector<int> &deads)
    {
        for (auto dead : deads) {
            auto find = _aiClients.find(dead);
            if (find != _aiClients.end()) {
                _connect.removeClient(dead);
                _aiClients.erase(find);
            }
        }
    }

    void Server::addClient()
    {
        static std::size_t id = 0;
        auto new_fd = _connect.acceptClient();
        _connect.addClient(new_fd);
        Shared::Connect::send(new_fd, "WELCOME\n");
        _newClients.emplace(new_fd, std::make_pair(id, std::string()));
        Shared::Utils::logMsg(
            _logFile, "New client[" + std::to_string(id) + "].");
        id++;
    }

    void Server::handleClient(const std::vector<int> &infos)
    {
        for (const auto fd : infos) {
            auto ai = _aiClients.find(fd);
            if (ai != _aiClients.end()) {
                handleAIClient(ai);
                continue;
            }
            auto gui = _guiClients.find(fd);
            if (gui != _guiClients.end()) {
                handleGUIClient(gui);
                continue;
            }
            auto newClient = _newClients.find(fd);
            if (newClient != _newClients.end())
                handleNewClient(newClient);
        }
    }

    void Server::handleAIClient(AIIter iter)
    {
        try {
            iter->second.infoToRead();
        } catch (Shared::Connect::CloseException &_) {
            _connect.removeClient(iter->first);
            _aiClients.erase(iter);
            Shared::Utils::logMsg(_logFile,
                "Client[" + std::to_string(iter->second.getId()) +
                    "] Close (Disconnected from the server).");
        }
    }

    void Server::handleGUIClient(GUIIter iter)
    {
        try {
            iter->second.infoToRead();
        } catch (Shared::Connect::CloseException &_) {
            _connect.removeClient(iter->first);
            _guiClients.erase(iter);
            Shared::Utils::logMsg(_logFile,
                "Client[" + std::to_string(iter->second.getId()) +
                    "] Close (Disconnected from the server).");
        }
    }

    std::optional<std::string> Server::getNewClientLine(
        std::unordered_map<int, NewClient>::iterator &iter)
    {
        bool close = false;

        try {
            Shared::Connect::receiveChunk(iter->first, iter->second.second);
        } catch (Shared::Connect::CloseException &_) {
            _connect.removeClient(iter->first);
            _newClients.erase(iter);
            Shared::Utils::logMsg(_logFile,
                "Client[" + std::to_string(iter->second.first) +
                    "] Close (Disconnected from the server).");
            close = true;
        }
        std::optional<std::string> line;
        if (!close)
            line = Shared::Utils::parseLine(iter->second.second);
        return line;
    }

    void Server::handleNewClient(
        std::unordered_map<int, NewClient>::iterator &iter)
    {
        auto line = getNewClientLine(iter);
        if (line.has_value()) {
            if (line.value() == GRAPHIC) {
                _guiClients.emplace(iter->first,
                    GUIClient(iter->first, iter->second.first, _logFile));
                _newClients.erase(iter);
                return;
            }
            auto find = _teams.find(line.value());
            if (find != _teams.end() && find->second > 0) {
                find->second--;
                _aiClients.emplace(iter->first,
                    AIClient(iter->first,
                        iter->second.first,
                        find->first,
                        _logFile,
                        _env));
                _newClients.erase(iter);
            } else {
                Shared::Connect::send(iter->first, "ko\n");
                _connect.removeClient(iter->first);
                _newClients.erase(iter);
                Shared::Utils::logMsg(_logFile,
                    "Client[" + std::to_string(iter->second.first) +
                        "] Close (Wrong Teams Selection).");
            }
        }
    }
}; // namespace Zappy
