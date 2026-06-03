/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Server
*/

#include <csignal>
#include <iostream>
#include <chrono>
#include <iomanip>
#include "Server.hpp"
#include "Utils.hpp"

namespace Zappy {

    bool Server::RECEIVED_SIG_INT = false;

    Server::Server(int port, std::vector<std::string> teams,
        std::size_t nbPerTeam) :
        _connect(port),
        _logFile(std::string(LOG_FILE))
    {
        logMsg("Server Open.");
        signal(SIGINT, [](int) {
            RECEIVED_SIG_INT = true;
        });
        for (auto team: teams)
            _teams.emplace(team, nbPerTeam);
    }

    Server::~Server()
    {
        logMsg("Server Close.");
    }

    void Server::run()
    {
        while (!RECEIVED_SIG_INT) {
            auto infos = _connect.infoToRead();
            if (infos.size() == 0)
                continue;
            if (infos[0] == _connect.getFd())
                addClient();
            handleClient(infos);
        }
    }

    void Server::addClient()
    {
        auto new_fd = _connect.acceptClient();
        _connect.addClient(new_fd);
        _connect.send(new_fd, "WELCOME\n");
        _newClients.emplace(new_fd, std::string());
        logMsg("New client.");
    }

    void Server::handleClient(const std::vector<int> &infos)
    {
        for (const auto fd: infos) {
            auto ai = _AIClients.find(fd);
            if (ai != _AIClients.end()) {
                ai->second.infoToRead();
                continue;
            }
            auto gui = _GUIClients.find(fd);
            if (gui != _GUIClients.end()) {
                gui->second.infoToRead();
                continue;
            }
            auto newClient = _newClients.find(fd);
            if (newClient != _newClients.end())
                handleNewClient(newClient);
        }
    }

    void Server::handleNewClient(
        std::unordered_map<int, std::string>::iterator &iter)
    {
        _connect.receiveChunk(iter->first, iter->second);        
        auto line = Shared::Utils::parseLine(iter->second);
        if (line.has_value()) {
            if (line.value() == GRAPHIC) {
                _GUIClients.emplace(iter->first, GUIClient(iter->first));
                _newClients.erase(iter);
                return;
            }
            auto find = _teams.find(line.value());
            if (find != _teams.end() && find->second > 0) {
                find->second--;
                _AIClients.emplace(iter->first, AIClient(iter->first));
                _newClients.erase(iter);
            } else {
                _connect.send(iter->first, "ko\n");
                _connect.removeClient(iter->first);
                _newClients.erase(iter);
            }
        }
    }

    void Server::logMsg(std::string msg)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        _logFile << "[" << std::put_time(std::localtime(&t), "%H:%M:%S") << "] ";
        _logFile << msg << std::endl;
    }
};
