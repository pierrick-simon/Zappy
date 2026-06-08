/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Transformable3D.hpp"

namespace Graphics {
    Maths::Vector3D &Transformable3D::getPosition()
    {
        return this->_position;
    }

    Maths::Quaternion &Transformable3D::getRotation()
    {
        return this->_rotation;
    }

    Maths::Vector3D &Transformable3D::getScale()
    {
        return this->_scale;
    }

    const Maths::Vector3D &Transformable3D::getPosition() const
    {
        return this->_position;
    }

    const Maths::Quaternion &Transformable3D::getRotation() const
    {
        return this->_rotation;
    }

    const Maths::Vector3D &Transformable3D::getScale() const
    {
        return this->_scale;
    }

    Maths::Vector3D Transformable3D::getForward() const
    {
        return Maths::FORWARD * this->getRotation();
    }
} // namespace Graphics
