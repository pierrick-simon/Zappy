/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Command
*/

#ifndef COMMAND_HPP
    #define COMMAND_HPP

    #include <string>

namespace Shared {
    class Command {
        public:
            Command(std::string str) : _str(str) {};

            std::string getStr() const {return _str;}

        private:
            std::string _str;
    };
}

#endif
