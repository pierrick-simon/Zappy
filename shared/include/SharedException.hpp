/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** SharedException
*/

#ifndef SHAREDEXCEPTION_HPP
    #define SHAREDEXCEPTION_HPP

    #include <exception>
    #include <string>

namespace Shared {
    class SharedException : public std::exception {
        public:
            SharedException(std::string str) : _str("Shared Error: " + str) {};

            virtual const char *what() const noexcept override
                    { return _str.c_str(); };
        private:
            std::string _str;
    };
}

#endif
