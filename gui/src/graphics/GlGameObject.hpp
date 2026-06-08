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
        explicit GLGameObject(sf::RenderWindow& window);

        void render() const final;
        virtual void preRender() const;
        virtual void glRender() const = 0;
        virtual void postRender() const;
    };
} // Graphics

#endif
