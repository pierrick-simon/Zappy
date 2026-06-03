/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AIClient
*/

#ifndef AICLIENT_HPP
    #define AICLIENT_HPP

    #include <fstream>
    #include<queue>

namespace Zappy {
    class AIClient {
        public:
            AIClient(int fd, std::size_t id, std::string team,
                std::ofstream &logFile);

            void infoToRead();

            std::size_t getId() const {return _id;}

        private:
            void addCommand();

            int _fd;
            std::size_t _id;
            std::string _team;
            std::ofstream &_logFile;
            std::string _buffer;
            std::queue<std::string> _command;

            static constexpr std::size_t MAX_QUEUE = 10;
    };
}

#endif
