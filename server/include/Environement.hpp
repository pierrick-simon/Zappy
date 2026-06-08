/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#ifndef ENVIRONEMENT_HPP
    #define ENVIRONEMENT_HPP

    #include <string>
    #include <unordered_map>
    #include <vector>

namespace Zappy {
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
        std::size_t _id;
        std::string _team;
    };

    struct TileInfo {
        std::vector<ResourceName> _resources;
        std::vector<Team> _eggs;
        std::vector<Team> _players;
    };

    class Environement {
    public:
        Environement(std::size_t width, std::size_t height, std::size_t freq);

        TileInfo getTileInfo(std::size_t width, std::size_t height);

        [[nodiscard]] std::size_t getHeight() const
        {
            return _height;
        }
        [[nodiscard]] std::size_t getWidth() const
        {
            return _width;
        }

    private:
        using Tile = std::vector<ResourceName>;

        struct Resource {
            float _density;
            std::string _str;
        };

        struct Egg {
            std::string _team;
            std::size_t _x;
            std::size_t _y;
        };

        struct Player {
            std::string _team;
            std::size_t _x;
            std::size_t _y;
        };

        std::size_t _width;
        std::size_t _height;
        std::size_t _freq;

        std::vector<Tile> _tiles;
        std::unordered_map<std::size_t, Egg> _eggs;
        std::unordered_map<std::size_t, Player> _players;
        static const std::unordered_map<ResourceName, Resource> _resources;
    };
} // namespace Zappy

#endif
