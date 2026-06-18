/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Map
*/

#include "Map.hpp"

#include <iostream>

#include "UtilsVector.hpp"

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
            this->setTilesPosition();
        }
        return value;
    }

    void Map::updateTile(
        std::size_t x, std::size_t y, const std::vector<std::size_t> &resources)
    {
        x %= _width;
        y %= _height;
        auto tileIndex = y * _width + x;
        auto &tile = _tiles[tileIndex];
        tile.updateTile(resources);
    }

    void Map::setTilesPosition()
    {
        float totalMapHeight =
            static_cast<float>(this->_height * TILE_HEIGHT) / 2.0f;
        float totalMapWidth =
            static_cast<float>(this->_width * TILE_WIDTH) / 2.0f;

        for (size_t i = 0; i < this->_tiles.size(); ++i) {
            size_t x = i / this->_width;
            size_t y = i % this->_width;
            this->_tiles[i].setPosition(
                {static_cast<float>(x * TILE_WIDTH) - totalMapWidth,
                    TILE_Y_POS,
                    static_cast<float>(y * TILE_HEIGHT) - totalMapHeight});
        }
    }
    void Map::setShader(Graphics::Shader &shader)
    {
        AShadered::setShader(shader);
        this->_model.materials[1].shader =
            static_cast<Shader>(this->getShader());
    }

    void Map::draw3D() const
    {
        for (const auto &tile : this->_tiles) {
            auto [axis, angle] = tile.getRotation().ToAxisAngle();
            this->_model.Draw(tile.getPosition(), axis, angle, tile.getScale());
        }
    }
} // namespace Zappy
