/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Tile
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

    #include <map>
    #include <queue>
    #include "Info.hpp"
    #include "Resource.hpp"

namespace Zappy {
    class Tile {
    public:
        Tile();

        void updateTile(const std::vector<std::size_t> &resources);

    private:
        void updateResource(std::queue<Resource> &resource, std::size_t nb,
            Info::ResourceName type);
        std::map<Info::ResourceName, std::queue<Resource>> _resources;
    };
} // namespace Zappy

#endif /* !TILE_HPP_ */
