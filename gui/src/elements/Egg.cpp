/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"
#include "Utils.hpp"
#include "UtilsVector.hpp"

namespace Zappy {
    Egg::Egg(std::size_t x, std::size_t y, std::string team,
        raylib::Vector2 pos, raylib::Model &eggModel) :
        _x(x), _y(y), _team(std::move(team)), _eggModel(eggModel)
    {
        auto scale = EGG_SCALE *
            Shared::Utils::fRandRange(
                1 - EGG_SCALE_MODIFIER, 1 + EGG_SCALE_MODIFIER);
        Transformable3D::setScale(raylib::Vector3 {scale, scale, scale});
        _position = raylib::Vector3 {
            pos.x + Shared::Utils::fRandRange(-RANGE.x, RANGE.x),
            0,
            pos.y + Shared::Utils::fRandRange(-RANGE.y, RANGE.y)};
    }

    std::size_t Egg::getTile(std::size_t mapWidth) const
    {
        return _y * mapWidth + _x;
    }

    void Egg::draw3D() const
    {
        _eggModel.Draw(
            this->getPosition(), Graphics::Vector3::ZERO, 0, this->getScale());
    }

    void Egg::initPos(std::size_t width, std::size_t height)
    {
        raylib::Vector2 mapSize = raylib::Vector2 {static_cast<float>(width),
                                      static_cast<float>(height)} *
            Tile::TILE_SIZE;
        raylib::Vector2 center =
            raylib::Vector2 {static_cast<float>(_x), static_cast<float>(_y)} *
                Tile::TILE_SIZE -
            mapSize / 2.0f;
        raylib::Vector3 pos(
            center.x + Shared::Utils::fRandRange(-RANGE.x, RANGE.x),
            0,
            center.y + Shared::Utils::fRandRange(-RANGE.y, RANGE.y));
        setPosition(pos);
    }
} // namespace Zappy
