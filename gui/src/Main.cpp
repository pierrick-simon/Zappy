/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Main
*/

#include <iostream>
#include "ArgsParser.hpp"
#include "GUI.hpp"
#include "GUIException.hpp"
#include "Help.hpp"
#include "Utils.hpp"

int main(const int ac, const char *const *av)
{
    std::vector<std::string> args;
    for (++av; *av != nullptr; ++av)
        args.emplace_back(*av);
    if (Parser::ArgsParser::isArg(args, "--help")) {
        Help::help("gui/docs/help.txt");
        return Shared::EPISUCCESS;
    }
    try {
        Zappy::GUI gui(args);
        gui.run();
    } catch (const Parser::Help &) {
        Help::help("gui/docs/help.txt");
        return Shared::EPIERROR;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        return Shared::EPIERROR;
    }
    return Shared::EPISUCCESS;
}
