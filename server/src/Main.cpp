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
#include "ArgsParser.hpp"
#include "Help.hpp"

int main(const int ac, const char *const *av)
{
    std::vector<std::string> args;
    for (++av;*av != NULL; ++av)
        args.emplace_back(*av);
    try {
        Zappy::Server server(args);
        server.run();
    } catch (const Parser::Help &) {
        Help::help("server/docs/help.txt");
        return Shared::EPIERROR;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return Shared::EPIERROR;
    }
    return Shared::EPISUCCESS;
}
