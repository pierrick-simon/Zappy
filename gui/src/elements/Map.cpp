/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Map
*/

#include "Map.hpp"

namespace Zappy {
    bool Map::updateSize(std::size_t x, std::size_t y)
    {
        bool value = true;
        if (x == _width && y == _height)
            value = false;
        else {
            _width = x;
            _height = y;
            _tiles.clear();
            _tiles.resize(_width * _height);
        }
        return value;
    }

    void Map::updateTile(
        std::size_t x, std::size_t y, const std::vector<std::size_t> &resources)
    {
        x %= _width;
        y %= _height;
        auto tile = y * _width + x;
        _tiles[tile].updateTile(resources);
    }
} // namespace Zappy
