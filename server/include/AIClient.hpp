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
    #include <optional>
    #include <queue>
    #include <unordered_map>
    #include "Environement.hpp"

namespace Zappy {
    class AIClient {
    public:
        AIClient(int fd, std::size_t id, std::string team,
            std::ofstream &logFile, Environement &_env);

        void infoToRead();

        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }

        [[nodiscard]] bool isAlive() const
        {
            return _alive;
        }

        [[nodiscard]] std::unordered_map<ResourceName, std::size_t>
        getInventory() const
        {
            return _inventory;
        }

        std::chrono::nanoseconds update(std::chrono::nanoseconds elapsed);
        void executeCommand();

    private:
        struct Command {
            std::function<void(AIClient &)> _func;
            std::chrono::nanoseconds _timeLimit;
        };

        using CommandIter =
            std::unordered_map<std::string, Command>::const_iterator;

        void addCommand();
        void checkAlive();

        int _fd;
        bool _alive = true;
        std::size_t _id;
        std::string _team;
        std::ofstream &_logFile;
        std::string _buffer;
        std::queue<std::string> _commands;
        std::chrono::nanoseconds _sleep;
        std::chrono::nanoseconds _live;
        std::optional<CommandIter> _command;

        std::unordered_map<ResourceName, std::size_t> _inventory;
        Environement &_env;

        static constexpr std::size_t MAX_QUEUE = 10;
        static constexpr std::size_t START_FOOD = 10;
        static constexpr std::chrono::nanoseconds CYCLE_TO_DIE =
            std::chrono::seconds(126);
        static constexpr std::chrono::nanoseconds DEFAULT_SLEEP =
            std::chrono::seconds(1);

        static const std::unordered_map<std::string, Command> COMMANDS;
    };
} // namespace Zappy

#endif
