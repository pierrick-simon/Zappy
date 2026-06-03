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

namespace Zappy {

    bool Server::RECEIVED_SIG_INT = false;

    Server::Server(int port) :
        _connect(port),
        _logFile(std::string(LOG_FILE))
    {
        logMsg("Server Open.");
        signal(SIGINT, [](int) {
            RECEIVED_SIG_INT = true;
        });
    }

    Server::~Server()
    {
        logMsg("Server Close.");
    }

    void Server::run()
    {
        while (!RECEIVED_SIG_INT);
    }

    void Server::logMsg(std::string msg)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        _logFile << "[" << std::put_time(std::localtime(&t), "%H:%M:%S") << "] ";
        _logFile << msg << std::endl;
    }
};
