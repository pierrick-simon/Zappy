/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Egg
*/

#ifndef EGG_HPP
    #define EGG_HPP

    #include <fstream>

namespace Zappy {
    class Egg {
    public:
        Egg(std::size_t x, std::size_t y, std::string team, std::ofstream &logFile);

    private:
        std::size_t _x;
        std::size_t _y;
        std::string _team;

        std::ofstream &_logFile;
    };
} // namespace Zappy

#endif
