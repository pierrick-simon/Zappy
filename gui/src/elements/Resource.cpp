/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Resource
*/

#include "Resource.hpp"
namespace Zappy {
    Resource::Resource(Info::ResourceName resource, Vector3 pos) :
        _resource(resource),
        _pos(pos)
    {
    }

    Vector3 Resource::getPos() const
    {
        return _pos;
    }

} // namespace Zappy
