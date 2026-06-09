/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Main
*/

#include <iostream>
#include "ArgsParser.hpp"
#include "Help.hpp"
#include "Server.hpp"
#include "ServerException.hpp"
#include "Utils.hpp"
#include "ArgsParser.hpp"

int main(const int ac, const char *const *av)
{
    std::vector<std::string> args;
    for (++av; *av != nullptr; ++av)
        args.emplace_back(*av);
    if (Parser::ArgsParser::isArg(args, "--help")) {
        Help::help("server/docs/help.txt");
        return Shared::EPISUCCESS;
    }
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
