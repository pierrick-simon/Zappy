/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Map
*/

#include "Map.hpp"
#include <iostream>
#include "Maths.hpp"
#include "Utils.hpp"
#include "UtilsVector.hpp"

namespace Zappy {
    Map::Map(std::size_t &width, std::size_t &height,
        std::optional<std::size_t> &select) :
        _width(width), _height(height), _select(select)
    {
        for (const auto &[type, infos] : Info::resources)
            _ressources_models.try_emplace(
                type, Assets::getResource("rocks/" + infos.str + ".glb"));
        for (std::size_t i = 0; i < NB_GRASS_MODELS; ++i)
            _grassModels[i] = raylib::Model(Assets::getResource(
                "grass/grass" + std::to_string(i) + ".glb"));
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
                    static_cast<float>(this->_height)} *
                Tile::TILE_SIZE;
            _tiles.clear();
            _tiles.resize(_width * _height);
            this->setTilesPosition();
            _totalResources = Info::INIT_RESOUCES;
            for (auto &tile : _tiles)
                tile.getScale() = TILE_SCALE;
            for (std::size_t i = 0; i < NB_GRASS; ++i) {
                _grasses[i].first = rand() % NB_GRASS_MODELS;
                _grasses[i].second = raylib::Vector3(
                    Shared::Utils::fRandRange(
                        0, static_cast<float>(_width) * Tile::TILE_SIZE.x),
                    0,
                    Shared::Utils::fRandRange(
                        0, static_cast<float>(_height) * Tile::TILE_SIZE.y));
            }
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
        auto before = tile.getNbResources();
        tile.updateTile(resources);
        auto after = tile.getNbResources();
        updateTotalResources(before, std::move(after));
    }

    void Map::setTilesPosition()
    {
        for (size_t i = 0; i < this->_tiles.size(); ++i) {
            size_t x = i % this->_width;
            size_t y = i / this->_width;
            this->_tiles[i].setPosition(
                {static_cast<float>(x) * Tile::TILE_SIZE.x -
                        this->_renderedMapSize.x / 2.0f,
                    TILE_Y_POS,
                    static_cast<float>(y) * Tile::TILE_SIZE.y -
                        this->_renderedMapSize.y / 2.0f});
        }
    }

    raylib::Vector2 Map::getTilePosition(size_t x, size_t y) const
    {
        return raylib::Vector2 {static_cast<float>(x), static_cast<float>(y)} *
            Tile::TILE_SIZE -
            this->_renderedMapSize / 2.0f;
    }

    void Map::setShader(Graphics::Shader &shader)
    {
        AShadered::setShader(shader);
        this->_tileModel.materials[1].shader = this->getShader().asShader();
    }

    void Map::drawGrass() const
    {
        for (std::size_t i = 0; i < NB_GRASS; ++i)
            _grassModels.at(_grasses[i].first)
                .Draw(_grasses[i].second, GRASS_SCALE);
    }

    void Map::drawRessources(const Zappy::Tile &tile) const
    {
        auto infos = tile.getResources();

        for (const auto &[type, queue_item] : infos) {
            auto &model = this->_ressources_models.at(type);
            const auto &resourceScale = _modelScales.at(type);
            for (const auto &item : queue_item) {
                auto itemScale = item.getScale();
                raylib::Vector3 scale(resourceScale * itemScale,
                    resourceScale * itemScale,
                    resourceScale * itemScale);
                auto [axis, angle] =
                    raylib::Quaternion::FromEuler(0, item.getRotation(), 0)
                        .ToAxisAngle();
                model.Draw(tile.getPosition() + item.getPos(),
                    axis,
                    Maths::RadToDeg(angle),
                    scale);
            }
        }
    }

    void Map::draw3D() const
    {
        std::size_t i = 0;
        for (const auto &tile : this->_tiles) {
            auto color = raylib::Color::White();
            if (_select && i == *_select && _changeColor) {
                color.r -= Init::BLINK_OFFSET;
                color.g -= Init::BLINK_OFFSET;
                color.b -= Init::BLINK_OFFSET;
            }
            auto [axis, angle] = tile.getRotation().ToAxisAngle();
            this->_tileModel.Draw(
                tile.getPosition(), axis, angle, tile.getScale(), color);
            drawRessources(tile);
            i++;
        }
        drawGrass();
    }

    void Map::update(float dt)
    {
        if (_blink <= 0) {
            _blink = Init::BLINK_TIME;
            _changeColor = !_changeColor;
        } else
            _blink -= dt;
    }

    std::map<Info::ResourceName, std::size_t> Map::getTileResources(
        std::size_t tile) const
    {
        return _tiles[tile].getNbResources();
    }

    std::size_t Map::getNextTile(InfoBox::Action dir, std::size_t tile) const
    {
        if (dir == InfoBox::Action::LEFT) {
            if (tile == 0)
                tile = _width * _height - 1;
            else
                tile--;
        } else if (dir == InfoBox::Action::RIGHT) {
            if (tile == _width * _height - 1)
                tile = 0;
            else
                tile++;
        }
        return tile;
    }

    const std::unordered_map<Info::ResourceName, float> Map::_modelScales = {
        {Info::ResourceName::FOOD, 0.07},
        {Info::ResourceName::LINEMATE, 0.035},
        {Info::ResourceName::DERAUMERE, 0.035},
        {Info::ResourceName::SIBUR, 0.035},
        {Info::ResourceName::MENDIANE, 0.035},
        {Info::ResourceName::PHIRAS, 0.035},
        {Info::ResourceName::THYSTAME, 0.035},
    };

} // namespace Zappy
