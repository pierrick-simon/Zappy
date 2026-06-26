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
        _resource(resource)
    {
        this->Transformable3D::setPosition(pos);
        this->Transformable3D::setScale({scale, scale, scale});
        this->Transformable3D::setRotation(
            raylib::Quaternion::FromEuler(0, rotation, 0));
    }
} // namespace Zappy
