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

    Map::Map()
    {
        for (const auto &[type, infos] : Info::resources)
            _ressources_models[type] =
                Assets::getResource("rocks/" + infos.str + ".glb");
    }

    bool Map::updateSize(std::size_t x, std::size_t y)
    {
        bool value = true;
        if (x == _width && y == _height)
            value = false;
        else {
            _width = x;
            _height = y;
            _renderedMapSize =
                raylib::Vector2 {static_cast<float>(this->_width),
                    static_cast<float>(this->_height)};
            _tiles.clear();
            _tiles.resize(_width * _height);
            this->setTilesPosition();
            _totalResources = Info::INIT_RESOUCES;
        }
        return value;
    }

    void Map::updateTotalResources(
        const std::map<Info::ResourceName, std::size_t> &before,
        std::map<Info::ResourceName, std::size_t> after)
    {
        for (const auto &[resource, nb] : before) {
            auto findAfter = after.find(resource);
            auto findTotal = _totalResources.find(resource);
            if (findTotal == _totalResources.end())
                continue;
            if (findAfter != after.end()) {
                findTotal->second = findTotal->second - nb + findAfter->second;
                after.erase(findAfter);
            } else
                findTotal->second -= nb;
        }
        for (const auto &[resource, nb] : after) {
            auto findTotal = _totalResources.find(resource);
            if (findTotal != _totalResources.end())
                findTotal->second += nb;
            else
                _totalResources.emplace(resource, nb);
        }
    }

    void Map::updateTile(
        std::size_t x, std::size_t y, const std::vector<std::size_t> &resources)
    {
        if (this->_width == 0 || this->_height == 0)
            return;
        x %= _width;
        y %= _height;
        auto tileIndex = y * _width + x;
        auto &tile = _tiles[tileIndex];
        auto before = tile.getResources();
        tile.updateTile(resources);
        auto after = tile.getResources();
        updateTotalResources(before, std::move(after));
    }

    void Map::setTilesPosition()
    {
        for (size_t i = 0; i < this->_tiles.size(); ++i) {
            size_t x = i / this->_width;
            size_t y = i % this->_width;
            this->_tiles[i].setPosition({static_cast<float>(x) * TILE_SIZE.x -
                    this->_renderedMapSize.x / 2.0f,
                TILE_Y_POS,
                static_cast<float>(y) * TILE_SIZE.y -
                    this->_renderedMapSize.y / 2.0f});
        }
    }

    raylib::Vector2 Map::getTilePosition(size_t x, size_t y) const
    {
        return raylib::Vector2 {static_cast<float>(x), static_cast<float>(y)} *
            TILE_SIZE -
            this->_renderedMapSize / 2.0f;
    }

    void Map::setShader(Graphics::Shader &shader)
    {
        AShadered::setShader(shader);
        this->_model.materials[1].shader = this->getShader().asShader();
    }

    void Map::drawRessources(const Zappy::Tile &tile) const
    {
        auto infos = tile.getResources();
        Vector3 vZero(0, 0, 0);
        Vector3 scale(0.05, 0.05, 0.05);

        for (const auto &[type, nb] : infos) {
            if (nb > 0)
                this->_ressources_models.at(type).Draw(
                    tile.getPosition(), vZero, 0, scale);
        }
    }

    void Map::draw3D() const
    {
        for (const auto &tile : this->_tiles) {
            auto [axis, angle] = tile.getRotation().ToAxisAngle();
            this->_model.Draw(tile.getPosition(), axis, angle, tile.getScale());
            drawRessources(tile);
        }
    }
} // namespace Zappy
