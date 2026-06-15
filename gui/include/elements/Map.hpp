/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include "Tile.hpp"

namespace Zappy {
    class Map {
    public:
        bool updateSize(std::size_t x, std::size_t y);
        void updateTile(std::size_t x, std::size_t y,
            const std::vector<std::size_t> &resources);

    private:
        std::size_t _width = 0;
        std::size_t _height = 0;
        std::vector<Tile> _tiles;
    };
} // namespace Zappy

#endif /* !MAP_HPP_ */
