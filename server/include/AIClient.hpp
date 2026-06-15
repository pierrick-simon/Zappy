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
    #include <map>
    #include <optional>
    #include <queue>
    #include <unordered_map>

namespace Zappy {

    class Environement;
    enum class ResourceName;

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

        [[nodiscard]] std::map<ResourceName, std::size_t> getInventory() const
        {
            return _inventory;
        }

        void setElevate(bool elevate)
        {
            _elevate = elevate;
        }

        std::chrono::nanoseconds update(std::chrono::nanoseconds elapsed);

    private:
        struct Command {
            std::function<void(AIClient &, std::istringstream &)> _func;
            std::chrono::nanoseconds _timeLimit;
        };

        using CommandIter =
            std::unordered_map<std::string, Command>::const_iterator;

        struct SelectCommand {
            CommandIter iter;
            std::istringstream &stream;
        };

        void addCommand();
        void checkAlive();
        void executeCommand();
        bool startCheckIncantation(const std::string &name);
        void eggLaying(const std::string &name);

        void forward(std::istringstream &);
        void right(std::istringstream &);
        void left(std::istringstream &);
        void look(std::istringstream &);
        void inventory(std::istringstream &);
        void connectNbr(std::istringstream &);
        void fork(std::istringstream &);
        void eject(std::istringstream &);
        void set(std::istringstream &);
        void take(std::istringstream &);
        void broadcast(std::istringstream &);

        int _fd;
        bool _alive = true;
        std::size_t _id;
        std::string _team;
        std::ofstream &_logFile;
        std::string _buffer;
        std::queue<std::string> _commands;
        std::chrono::nanoseconds _sleep;
        std::chrono::nanoseconds _live;
        std::optional<SelectCommand> _command;
        bool _elevate = false;

        std::map<ResourceName, std::size_t> _inventory;
        std::vector<std::size_t> _elevationPlayers;
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
