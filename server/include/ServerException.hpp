/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** ServerException
*/

#ifndef SERVEREXCEPTION_HPP
    #define SERVEREXCEPTION_HPP

    #include <exception>
    #include <string>

namespace Zappy {
    class ServerException : public std::exception {
    public:
        ServerException(const std::string &str) :
            _str("Server Error: " + str) {};

        [[nodiscard]] const char *what() const noexcept override
        {
            return _str.c_str();
        };

    private:
        std::string _str;
    };
} // namespace Zappy

#endif
