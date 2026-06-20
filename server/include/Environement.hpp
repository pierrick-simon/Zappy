/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#ifndef ENVIRONEMENT_HPP
    #define ENVIRONEMENT_HPP

    #include <chrono>
    #include <concepts>
    #include <map>
    #include <ranges>
    #include <string>
    #include <unordered_map>
    #include <vector>
    #include "Client.hpp"
    #include "GUIEvent.hpp"
    #include "Info.hpp"
    #include "Vector.hpp"

namespace Zappy {
    enum class Movement { Forward, Backward };

    enum class Rotate { Left, Right };

    struct Team {
        std::size_t id;
        std::string team;
    };

    struct TileInfo {
        std::map<Info::ResourceName, std::size_t> resources;
        std::vector<Team> eggs;
        std::vector<Team> players;
    };

    struct PlayerInfo {
        std::size_t x = 0;
        std::size_t y = 0;
        std::size_t dir = 0;
        std::size_t level = 0;
        std::string team;
        std::map<Info::ResourceName, std::size_t> inventory = {};
    };

    class AIClient;
    class GUIClient;

    class Environement {
    public:
        Environement(std::size_t width, std::size_t height,
            std::ofstream &logFile, Clients &clients,
            std::unordered_map<std::string, std::size_t> &teams);

        Environement(Environement &) = delete;

        std::chrono::milliseconds update(std::chrono::milliseconds elapsed);
        TileInfo getTileInfo(std::size_t width, std::size_t height) const;

        std::string formatTile(std::size_t width, std::size_t height) const;
        std::string lookAround(std::size_t id);
        void newGuiInfo(int fd);
        void addPlayer(std::size_t id, const std::string &team,
            std::size_t _remainingPlace);
        void removePlayer(std::unordered_map<int, AIClient>::iterator);
        void movePlayer(std::size_t id);
        void rotatePlayer(std::size_t id, Rotate);
        void spawnEgg(std::size_t id);
        void spawnEgg(const std::string &team);
        void eggLaying(std::size_t id);
        bool takeResource(std::size_t id, Info::ResourceName);
        void setResource(std::size_t id, Info::ResourceName);
        bool eject(std::size_t id);
        bool startElevation(std::size_t id);
        void endElevation(std::size_t x, std::size_t y, std::size_t level,
            std::vector<std::size_t>, std::size_t id);
        void broadcast(std::size_t id, const std::string &text);
        void playerEat(std::size_t id,
            const std::map<Info::ResourceName, std::size_t> &inventory);

        static const std::unordered_map<std::size_t,
            std::pair<Shared::Vector2<double>, Shared::Vector2<double>>>
            _broadcastChunks;

        [[nodiscard]] std::size_t getHeight() const
        {
            return _height;
        }
        [[nodiscard]] std::size_t getWidth() const
        {
            return _width;
        }
        [[nodiscard]] bool getEnd() const
        {
            return _end;
        }
        [[nodiscard]] std::size_t getConnectNbr(std::size_t) const;
        [[nodiscard]] std::vector<std::string> getTeamsName() const;
        [[nodiscard]] PlayerInfo getPlayerInfo(std::size_t id) const;

    private:
        struct Egg {
            std::string team;
            std::size_t x;
            std::size_t y;
        };

        using EggIter =
            std::unordered_map<std::size_t, Zappy::Environement::Egg>::iterator;

        struct Player {
            std::string team;
            Info::Direction dir;
            std::size_t level;
            bool elevation;
            std::size_t x;
            std::size_t y;
        };

        using PlayerIter = std::unordered_map<std::size_t,
            Zappy::Environement::Player>::iterator;

        struct Elevate {
            std::chrono::milliseconds sleep;
            std::size_t x;
            std::size_t y;
            std::size_t level;
            std::vector<std::size_t> players;
            std::size_t id;
        };

        static std::size_t circularMove(
            std::size_t pos, int delta, std::size_t size);
        std::vector<std::size_t> checkElevation(
            std::size_t x, std::size_t y, std::size_t level, bool elevated);
        void successElevation(std::size_t x, std::size_t y,
            const Info::Elevation &, const std::vector<size_t> &players,
            std::size_t level);
        void failElevation(const std::vector<size_t> &players, std::size_t id);
        void setResource(
            std::size_t tile, Info::ResourceName name, std::size_t nb);
        int getPlayerFd(std::size_t id);
        void setPlayerElevate(std::size_t id, bool value);
        void handleEjectPlayer(PlayerIter, Info::Direction);
        EggIter handleDestroyEgg(EggIter);
        void checkEnd();
        std::vector<std::size_t> getTileValue(std::size_t tile);

        bool refillRessource(Info::ResourceName type, std::size_t count);
        void refillRessources(const bool &log = true);

        Shared::Vector2<int> getBroadCastVector(
            const Player &sender, const Player &receiver) const;
        static std::size_t getTileNb(
            const Player &receiver, const Shared::Vector2<int> &v);

        template<std::derived_from<Shared::GUIEvent> EventType,
            typename... Args>
        void sendToGUI(Args &&...args)
        {
            EventType event(std::forward<Args>(args)...);
            event.send(std::vector<int>(std::views::keys(_clients.gui).begin(),
                std::views::keys(_clients.gui).end()));
        }

        std::size_t _width;
        std::size_t _height;
        std::size_t _eggId = 0;
        std::chrono::milliseconds _sleep;
        bool _end = false;

        std::vector<Info::Tile> _tiles;
        std::unordered_map<std::size_t, Egg> _eggs;
        std::unordered_map<std::size_t, Player> _players;
        std::vector<Elevate> _elevates;

        std::ofstream &_logFile;
        Clients &_clients;
        std::unordered_map<std::string, std::size_t> &_teams;

        static constexpr std::chrono::milliseconds SLEEP =
            std::chrono::seconds(20);
        static constexpr std::chrono::milliseconds ELEVATE =
            std::chrono::seconds(300);
        static constexpr std::size_t MAX_LEVEL = 8;
        static constexpr std::size_t WIN = 6;
    };
} // namespace Zappy

#endif
