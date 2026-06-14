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
    #include <optional>
    #include <queue>
    #include <unordered_map>
    #include "Environement.hpp"

namespace Zappy {
    class GUIClient {
    public:
        GUIClient(int fd, std::size_t id, std::ofstream &logFile,
            Environement &env, std::size_t f);

        void infoToRead();

        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }

        [[nodiscard]] std::optional<std::size_t> timeUnitUpdate();

        void tileInfoEvent(std::size_t x, std::size_t y,
            const std::map<ResourceName, std::size_t> &resources) const;
        void playerPositionEvent(std::size_t id, std::size_t x, std::size_t y,
            std::size_t dir) const;
        void newPlayerEvent(std::size_t id, std::size_t x, std::size_t y,
            std::size_t dir, const std::string &team) const;
        void timeUnitEvent(std::size_t f);
        void playerExpulsionEvent(std::size_t id) const;
        void eggDestroyEvent(std::size_t id) const;

    private:
        using Command = std::function<void(GUIClient &, std::istringstream &)>;

        void addCommand();
        void update();

        void mapSize(std::istringstream &);
        void tileInfo(std::istringstream &);
        void tilesInfo(std::istringstream &);
        void teamsName(std::istringstream &);
        void playerPosition(std::istringstream &);
        void playerLevel(std::istringstream &);
        void playerInventory(std::istringstream &);
        void getTimeUnit(std::istringstream &) const;
        void setTimeUnit(std::istringstream &);

        int _fd;
        std::size_t _id;
        std::ofstream &_logFile;
        std::string _buffer;
        std::queue<std::string> _commands;
        std::optional<std::size_t> _requestF;

        std::size_t _f;
        Environement &_env;

        static const std::unordered_map<std::string, Command> COMMANDS;
    };
} // namespace Zappy

#endif
