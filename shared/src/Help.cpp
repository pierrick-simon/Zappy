/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Help
*/

#include "Help.hpp"

void Help::help(const std::string &path) noexcept
{
    std::ifstream helpfile(path);
    std::string line;

    while (std::getline(helpfile, line))
        std::cerr << line << std::endl;
}
