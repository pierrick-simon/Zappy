/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AIClient
*/

#ifndef AICLIENT_HPP
    #define AICLIENT_HPP

    #include <chrono>
    #include <fstream>
    #include <functional>
    #include <iomanip>
    #include <queue>
    #include <unordered_map>

namespace Zappy {
    class AIClient {
    public:
        AIClient(
            int fd, std::size_t id, std::string team, std::ofstream &logFile);

        void infoToRead();

        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }

        void update(std::chrono::nanoseconds elapsed);

    private:
        struct Command {
            std::function<void(AIClient &)> _func;
            std::chrono::nanoseconds _timeLimit;
        };

        void addCommand();

        int _fd;
        std::size_t _id;
        std::string _team;
        std::ofstream &_logFile;
        std::string _buffer;
        std::queue<std::string> _command;
        std::chrono::nanoseconds _sleep;

        static constexpr std::size_t MAX_QUEUE = 10;

        static const std::unordered_map<std::string, Command> COMMANDS;
    };
} // namespace Zappy

#endif
