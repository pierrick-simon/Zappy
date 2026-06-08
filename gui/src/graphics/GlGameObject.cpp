/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include <SFML/Graphics.hpp>

#include "GlGameObject.hpp"

namespace Graphics
{
    GLGameObject::GLGameObject(): GameObject()
    {
    }

    void GLGameObject::draw(sf::RenderTarget &target,
        sf::RenderStates states) const
    {
        this->preDraw(target);
        this->glDraw();
        this->postDraw(target);
    }


    void GLGameObject::preDraw(sf::RenderTarget& target) const
    {
        target.setActive();
        target.popGLStates();
    }

    void GLGameObject::postDraw(sf::RenderTarget& target) const
    {
        target.pushGLStates();
    }
} // Graphics