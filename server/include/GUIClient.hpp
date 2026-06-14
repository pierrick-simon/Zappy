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
    #include <map>
    #include <optional>
    #include <queue>
    #include <unordered_map>
    #include "GUIEvent.hpp"

namespace Zappy {

    class Environement;
    enum class ResourceName;

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

        void timeUnitEvent(std::size_t f);
        void broadcastEvent(std::size_t id, const std::string &text) const;
        void eggLayingEvent(std::size_t egg, std::size_t player, std::size_t x,
            std::size_t y) const;
        void resourceDroppingEvent(std::size_t id, std::size_t resource) const;
        void resourceCollectingEvent(
            std::size_t id, std::size_t resource) const;
        void endOfGameEvent(const std::string &team) const;
        void serverMsgEvent(const std::string &msg) const;

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

        template<std::derived_from<Shared::GUIEvent> EventType,
            typename... Args>
        void send(Args &&...args)
        {
            EventType event(std::forward<Args>(args)...);
            event.send({_fd});
        }

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
