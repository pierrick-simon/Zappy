/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUIClient
*/

#ifndef GUICLIENT_HPP
    #define GUICLIENT_HPP

    #include <fstream>
    #include <queue>

namespace Zappy {
    class GUIClient {
    public:
        GUIClient(int fd, std::size_t id, std::ofstream &logFile);

        void infoToRead();

        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }

    private:
        void addCommand();

        int _fd;
        std::size_t _id;
        std::ofstream &_logFile;
        std::string _buffer;
        std::queue<std::string> _command;
    };
} // namespace Zappy

#endif
