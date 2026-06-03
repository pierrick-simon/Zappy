/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Utils
*/

#include "Utils.hpp"

namespace Shared {
    std::optional<std::string> Utils::parseLine(std::string &str)
    {
        std::optional<std::string> line;
        std::size_t pos = str.find('\n');
        if (pos != std::string::npos) {
            line = str.substr(0, pos);
            if (!line->empty() && line->back() == '\r')
                line->pop_back();
            str.erase(0, pos + 1);
        }
        return line;
    }
}