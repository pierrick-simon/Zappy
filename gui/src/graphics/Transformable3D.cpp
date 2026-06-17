/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Transformable3D.hpp"

#include "UtilsVector.hpp"

namespace Graphics {
    raylib::Vector3 &Transformable3D::getPosition()
    {
        return this->_position;
    }

    raylib::Quaternion &Transformable3D::getRotation()
    {
        return this->_rotation;
    }

    raylib::Vector3 &Transformable3D::getScale()
    {
        return this->_scale;
    }

    void Transformable3D::setPosition(raylib::Vector3 position)
    {
        this->_position = position;
    }

    void Transformable3D::setRotation(raylib::Quaternion rotation)
    {
        this->_rotation = rotation;
    }

    void Transformable3D::setScale(raylib::Vector3 scale)
    {
        this->_scale = scale;
    }

    const raylib::Vector3 &Transformable3D::getPosition() const
    {
        return this->_position;
    }

    const raylib::Quaternion &Transformable3D::getRotation() const
    {
        return this->_rotation;
    }

    const raylib::Vector3 &Transformable3D::getScale() const
    {
        return this->_scale;
    }

    raylib::Vector3 Transformable3D::getForward() const
    {
        return Vector3::FORWARD.RotateByQuaternion(this->getRotation());
    }
} // namespace Graphics
