/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Info
*/

#ifndef INFO_HPP
    #define INFO_HPP

    #include <map>
    #include <string>
    #include <unordered_map>
    #include "SharedException.hpp"

namespace Zappy {
    class Info {
    public:
        enum class Direction { NORTH, WEST, SOUTH, EAST };

        enum class ResourceName {
            FOOD,
            LINEMATE,
            DERAUMERE,
            SIBUR,
            MENDIANE,
            PHIRAS,
            THYSTAME
        };

        struct Resource {
            float density;
            std::string str;
            std::size_t nb;
        };

        struct Dir {
            int x;
            int y;
            std::string str;
            std::size_t nb;
        };

        using Tile = std::map<ResourceName, std::size_t>;

        struct Elevation {
            std::size_t nbPlayer;
            Tile resources;
        };

        static const std::unordered_map<ResourceName, Resource> resources;
        static const std::map<ResourceName, std::size_t> INIT_RESOUCES;
        static const std::map<Direction, Dir> directions;
        static const std::unordered_map<std::size_t, Elevation> elevations;

        static std::string getResourceName(ResourceName name)
        {
            return resources.at(name).str;
        }

        static ResourceName getResource(const std::string &name);
        static ResourceName getResource(std::size_t nb);
        static Direction getDirection(std::size_t nb);

        class ResourceNotFoundException : public Shared::SharedException {
        public:
            ResourceNotFoundException() :
                Shared::SharedException("Resource not found.") {};
        };

        class DirectionNotFoundException : public Shared::SharedException {
        public:
            DirectionNotFoundException() :
                Shared::SharedException("Direction not found.") {};
        };
    };
} // namespace Zappy

#endif
