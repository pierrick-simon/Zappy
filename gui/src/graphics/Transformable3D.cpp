/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Transformable3D.hpp"

namespace Graphics {
    Vector3 &Transformable3D::getPosition()
    {
        return this->_position;
    }

    Quaternion &Transformable3D::getRotation()
    {
        return this->_rotation;
    }

    Vector3 &Transformable3D::getScale()
    {
        return this->_scale;
    }

    const Vector3 &Transformable3D::getPosition() const
    {
        return this->_position;
    }

    const Quaternion &Transformable3D::getRotation() const
    {
        return this->_rotation;
    }

    const Vector3 &Transformable3D::getScale() const
    {
        return this->_scale;
    }

    Vector3 Transformable3D::getForward() const
    {
        return Vector3RotateByQuaternion(Vector3UnitZ, this->getRotation());
    }
} // namespace Graphics
