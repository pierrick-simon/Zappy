/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#ifndef ENVIRONEMENT_HPP
    #define ENVIRONEMENT_HPP

    #include <chrono>
    #include <map>
    #include <string>
    #include <unordered_map>
    #include <vector>

namespace Zappy {
    enum class Direction { North, East, South, West };

    enum class Movement { Forward, Backward };

    enum class Rotate { Left, Right };

    enum class ResourceName {
        Food,
        Linemate,
        Deraumere,
        Sibur,
        Mendiane,
        Phiras,
        Thystame
    };

    struct Team {
        std::size_t id;
        std::string team;
    };

    struct TileInfo {
        std::unordered_map<ResourceName, std::size_t> resources;
        std::vector<Team> eggs;
        std::vector<Team> players;
    };

    struct Clients;
    class AIClient;
    class GUIClient;

    class Environement {
    public:
        Environement(std::size_t width, std::size_t height,
            std::ofstream &logFile, Clients &clients,
            std::unordered_map<std::string, std::size_t> &teams);

        std::chrono::nanoseconds update(std::chrono::nanoseconds elapsed);
        TileInfo getTileInfo(std::size_t width, std::size_t height) const;

        void addPlayer(std::size_t id, const std::string &team,
            std::size_t _remainingPlace);
        void removePlayer(std::unordered_map<int, AIClient>::iterator);
        void movePlayer(std::size_t id);
        void rotatePlayer(std::size_t id, Rotate);
        void spawnEgg(std::size_t id);
        void spawnEgg(const std::string &team);
        static Direction getOpositeDir(Direction);
        bool takeResource(std::size_t id, ResourceName);
        void setResource(std::size_t id, ResourceName);
        bool eject(std::size_t id);
        std::vector<std::size_t> startElevation(std::size_t id);
        void endElevation(std::size_t id, std::vector<std::size_t>);

        [[nodiscard]] std::size_t getHeight() const
        {
            return _height;
        }
        [[nodiscard]] std::size_t getWidth() const
        {
            return _width;
        }
        static std::string getResourceName(ResourceName name)
        {
            return _resources.at(name).str;
        }
        [[nodiscard]] std::size_t getConnectNbr(std::size_t) const;

        static ResourceName getResource(const std::string &name);

    private:
        using Tile = std::unordered_map<ResourceName, std::size_t>;

        struct Resource {
            float density;
            std::string str;
        };

        struct Egg {
            std::string team;
            std::size_t x;
            std::size_t y;
        };

        struct Player {
            std::string team;
            Direction dir;
            std::size_t level;
            bool elevation;
            std::size_t x;
            std::size_t y;
        };

        struct Dir {
            int x;
            int y;
            std::string str;
        };

        struct Elevation {
            std::size_t nbPlayer;
            Tile resources;
        };

        static std::size_t circularMove(
            std::size_t pos, int delta, std::size_t size);
        std::vector<std::size_t> checkElevation(
            std::size_t x, std::size_t y, std::size_t level);
        void successElevation(std::size_t x, std::size_t y, const Elevation &,
            const std::vector<size_t> &player);
        void setResource(std::size_t tile, ResourceName name, std::size_t nb);

        std::size_t _width;
        std::size_t _height;
        std::size_t _eggId = 0;
        std::chrono::nanoseconds _sleep;

        std::vector<Tile> _tiles;
        std::unordered_map<std::size_t, Egg> _eggs;
        std::unordered_map<std::size_t, Player> _players;

        std::ofstream &_logFile;
        Clients &_clients;
        std::unordered_map<std::string, std::size_t> &_teams;

        static const std::unordered_map<ResourceName, Resource> _resources;
        static const std::map<Direction, Dir> _directions;
        static const std::unordered_map<std::size_t, Elevation> _elevations;

        static constexpr std::chrono::nanoseconds SLEEP =
            std::chrono::seconds(20);
    };
} // namespace Zappy

#endif
