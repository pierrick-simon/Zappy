/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef SFMLGAMEOBJECT_HPP
    #define SFMLGAMEOBJECT_HPP
    #include "GameObject.hpp"

namespace Graphics {
    class SFMLGameObject : public GameObject {
    public:
        explicit SFMLGameObject();

    protected:
        void draw(
            sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void preDraw(sf::RenderTarget &target) const;
        virtual void glDraw() const = 0;
        virtual void postDraw(sf::RenderTarget &target) const;
    };
} // namespace Graphics

#endif
