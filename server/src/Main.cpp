/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Main
*/

#include <iostream>
#include "Server.hpp"
#include "ServerException.hpp"
#include "Utils.hpp"

int main(const int ac, const char *const *av)
{
    std::vector<std::string> args;
    for (++av;*av != NULL; ++av)
        args.emplace_back(*av);
    try {
        Zappy::Server server(args);
        server.run();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
        return Shared::EPIERROR;
    }
    return Shared::EPISUCCESS;
}
