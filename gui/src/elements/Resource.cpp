/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Resource
*/

#include "Resource.hpp"
namespace Zappy {
    Resource::Resource(
        Info::ResourceName resource, raylib::Vector3 pos, float scale) :
        _resource(resource), _pos(pos), _scale(scale)
    {
    }

    raylib::Vector3 Resource::getPos() const
    {
        return _pos;
    }

    float Resource::getScale() const
    {
        return _scale;
    }

} // namespace Zappy
