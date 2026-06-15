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
        Egg(std::string team);

    private:
        std::string _team;
    };
} // namespace Zappy

#endif
