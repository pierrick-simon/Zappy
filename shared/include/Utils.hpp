/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Utils
*/

#ifndef UTILS_HPP
    #define UTILS_HPP

    #include <chrono>
    #include <fstream>
    #include <optional>
    #include <string>

namespace Shared {
    constexpr int EPISUCCESS = 0;
    constexpr int EPIERROR = 84;
    constexpr int SKIP = -1;
    constexpr int EXIT = 1;

    using Clock = std::chrono::_V2::steady_clock::time_point;

    class Utils {
    public:
        static std::optional<std::string> parseLine(std::string &str);
        static void logMsg(std::ofstream &file, const std::string &msg);
        static float fRandRange(float min, float max);
        static double radToPos(double rad);
    };
} // namespace Shared

#endif
