/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#ifndef ENVIRONEMENT_HPP
    #define ENVIRONEMENT_HPP

    #include <map>
    #include <string>
    #include <unordered_map>
    #include <vector>

namespace Zappy {
    enum class Direction { North, East, South, West };

    enum class Movement { Forward, Backward };

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

    class Environement {
    public:
        Environement(std::size_t width, std::size_t height, std::size_t freq,
            std::ofstream &logFile);

        TileInfo getTileInfo(std::size_t width, std::size_t height) const;

        void addPlayer(std::size_t id, const std::string &team,
            std::size_t _remainingPlace);
        void removePlayer(std::size_t id);
        void movePlayer(std::size_t id, Direction dir);
        static Direction getOpositeDir(Direction);
        bool takeResource(std::size_t id, ResourceName);
        void setResource(std::size_t id, ResourceName);
        std::vector<std::size_t> startElevation(std::size_t id);
        std::vector<std::size_t> endElevation(
            std::size_t id, std::vector<std::size_t>);

        [[nodiscard]] std::size_t getHeight() const
        {
            return _height;
        }
        [[nodiscard]] std::size_t getWidth() const
        {
            return _width;
        }
        [[nodiscard]] std::size_t getFreq() const
        {
            return _freq;
        }

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
        bool successElevation(std::size_t x, std::size_t y, const Elevation &,
            const std::vector<size_t> &player);

        std::size_t _width;
        std::size_t _height;
        std::size_t _freq;

        std::vector<Tile> _tiles;
        std::unordered_map<std::size_t, Egg> _eggs;
        std::unordered_map<std::size_t, Player> _players;

        std::ofstream &_logFile;

        static const std::unordered_map<ResourceName, Resource> _resources;
        static const std::map<Direction, Dir> _directions;
        static const std::unordered_map<std::size_t, Elevation> _elevations;
    };
} // namespace Zappy

#endif
