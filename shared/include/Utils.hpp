/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Utils
*/

#ifndef UTILS_HPP
    #define UTILS_HPP

    #include <string>
    #include <optional>

namespace Shared {
    constexpr int EPISUCCESS = 0;
    constexpr int EPIERROR = 84;
    constexpr int SKIP = -1;
    constexpr int EXIT = 1;

    class Utils {
        public:
            static std::optional<std::string> parseLine(std::string &str);
    };
} 

#endif