/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include <SFML/Graphics.hpp>

#include "GlGameObject.hpp"

#include <iostream>

namespace Graphics
{
    GLGameObject::GLGameObject(sf::RenderWindow &window): GameObject(window)
    {
    }

    void GLGameObject::render() const
    {
        this->preRender();
        this->glRender();
        this->postRender();
    }

    void GLGameObject::preRender() const
    {
        this->_window.setActive();
        this->_window.popGLStates();
    }

    void GLGameObject::postRender() const
    {
        this->_window.pushGLStates();
    }
} // Graphics