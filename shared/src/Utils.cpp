/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Utils
*/

#include <chrono>
#include <iomanip>
#include <iostream>
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

    void Utils::logMsg(std::ofstream &file, const std::string &msg)
    {
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        file << "[" << std::put_time(std::localtime(&t), "%H:%M:%S") << "] ";
        file << msg << std::endl;
        std::cout << "[" << std::put_time(std::localtime(&t), "%H:%M:%S");
        std::cout << "] " << msg << std::endl;
    }
}