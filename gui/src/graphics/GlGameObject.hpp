/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef OPENGLGAMEOBJECT_HPP
    #define OPENGLGAMEOBJECT_HPP
    #include "GameObject.hpp"

namespace Graphics {
    class GLGameObject : public GameObject {
    public:
        explicit GLGameObject();

    protected:
        void draw(
            sf::RenderTarget &target, sf::RenderStates states) const override;
        virtual void preDraw(sf::RenderTarget &target) const;
        virtual void glDraw() const = 0;
        virtual void postDraw(sf::RenderTarget &target) const;
    };
} // namespace Graphics

#endif
