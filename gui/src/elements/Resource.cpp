/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Resource
*/

#include "Resource.hpp"
namespace Zappy {
    Resource::Resource(Info::ResourceName resource, raylib::Vector3 pos,
        float scale, float rotation) :
        _resource(resource), _pos(pos), _scale(scale), _rotation(rotation)
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

    float Resource::getRotation() const
    {
        return _rotation;
    }

} // namespace Zappy
