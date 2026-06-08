/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include <SFML/Graphics.hpp>

#include "SFMLGameObject.hpp"

namespace Graphics {
    SFMLGameObject::SFMLGameObject() :
        GameObject()
    {
    }

    void SFMLGameObject::draw(
        sf::RenderTarget &target, sf::RenderStates states) const
    {
        this->preDraw(target);
        // this->glDraw();
        this->postDraw(target);
    }

    void SFMLGameObject::preDraw(sf::RenderTarget &target) const
    {
        target.setActive();
        target.pushGLStates();
    }

    void SFMLGameObject::postDraw(sf::RenderTarget &target) const
    {
        target.popGLStates();
    }
} // namespace Graphics
