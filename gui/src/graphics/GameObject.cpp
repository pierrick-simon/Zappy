/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "GameObject.hpp"

namespace Graphics {
    GameObject::GameObject(sf::RenderWindow &window) :
        _window(window)
    {
    }

    void GameObject::render() const
    {
    }

    Maths::Vector3D &GameObject::getPosition()
    {
        return this->_position;
    }

    Maths::Quaternion &GameObject::getRotation()
    {
        return this->_rotation;
    }

    Maths::Vector3D &GameObject::getScale()
    {
        return this->_scale;
    }

    const Maths::Vector3D &GameObject::getPosition() const
    {
        return this->_position;
    }

    const Maths::Quaternion &GameObject::getRotation() const
    {
        return this->_rotation;
    }

    const Maths::Vector3D &GameObject::getScale() const
    {
        return this->_scale;
    }

    Maths::Vector3D GameObject::getForward() const
    {
        return Maths::FORWARD * this->getRotation();
    }

} // Graphics
