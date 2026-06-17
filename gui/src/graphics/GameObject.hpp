/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef GAMEOBJECT_HPP
    #define GAMEOBJECT_HPP

    #include "Transformable3D.hpp"
    #include "graphics/Drawable.hpp"

namespace Graphics {
    class GameObject : public Transformable3D, public Drawable {
    public:
        virtual void update(float dt) = 0;
    };
} // namespace Graphics

#endif
