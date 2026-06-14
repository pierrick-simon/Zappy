/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUIClient
*/

#ifndef GUICLIENT_HPP
    #define GUICLIENT_HPP

    #include <fstream>
    #include <functional>
    #include <iomanip>
    #include <queue>
    #include <unordered_map>
    #include "Environement.hpp"

namespace Zappy {
    class GUIClient {
    public:
        GUIClient(
            int fd, std::size_t id, std::ofstream &logFile, Environement &env);

        void infoToRead();

        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }

    private:
        using Command = std::function<void(GUIClient &, std::istringstream &)>;

        void addCommand();
        void update();

        void mapSize(std::istringstream &);
        void tileInfo(std::istringstream &);
        void tilesInfo(std::istringstream &);
        void teamsName(std::istringstream &);

        int _fd;
        std::size_t _id;
        std::ofstream &_logFile;
        std::string _buffer;
        std::queue<std::string> _commands;

        Environement &_env;

        static const std::unordered_map<std::string, Command> COMMANDS;
    };
} // namespace Zappy

#endif
