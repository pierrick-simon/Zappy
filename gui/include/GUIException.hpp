/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUIException
*/

#ifndef GUIEXCEPTION_HPP
    #define GUIEXCEPTION_HPP

    #include <exception>
    #include <string>

namespace Zappy {
    class GUIException : public std::exception {
        public:
            GUIException(const std::string &str) : _str("GUI Error: " + str) {};

            [[nodiscard]] const char *what() const noexcept override
                    { return _str.c_str(); };
        private:
            std::string _str;
    };
}

#endif
