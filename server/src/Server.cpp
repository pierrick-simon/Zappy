/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Server
*/

#include <csignal>
#include <iostream>
#include "Server.hpp"

namespace Zappy {

    bool Server::RECEIVED_SIG_INT = false;

    Server::Server(int port) :
        _connect(port)
    {
        signal(SIGINT, [](int) {
            std::cout << "Received SIGINT: Stopping the server." << std::endl;
            RECEIVED_SIG_INT = true;
        });
    }

    void Server::run()
    {
        while (!RECEIVED_SIG_INT);
    }
};
