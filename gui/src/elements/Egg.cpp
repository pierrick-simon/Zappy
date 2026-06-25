/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Egg
*/

#include "Egg.hpp"
#include "UtilsVector.hpp"

namespace Zappy {
    Egg::Egg(std::size_t x, std::size_t y, std::string team,
        raylib::Vector2 pos, raylib::Model &eggModel) :
        _x(x), _y(y), _team(std::move(team)), _eggModel(eggModel)
    {
        setPosition(raylib::Vector3 {pos.x, 0, pos.y});
        setScale(raylib::Vector3 {EGG_SCALE, EGG_SCALE, EGG_SCALE});
    }

    std::size_t Egg::getTile(std::size_t mapWidth) const
    {
        return _y * mapWidth + _x;
    }

    void Egg::draw3D() const
    {
        _eggModel.Draw(this->getPosition(), Graphics::Vector3::ZERO, 0, this->getScale());
    }
} // namespace Zappy
