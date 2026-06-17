/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef GAMEOBJECT_HPP
    #define GAMEOBJECT_HPP

    #include "Transformable3D.hpp"
    #include "graphics/IDrawable3D.hpp"
    #include "graphics/IObject.hpp"
    #include "graphics/IUpdatable.hpp"

namespace Graphics {
    class GameObject : public Transformable3D,
                       public IDrawable3D,
                       public IUpdatable,
                       public IObject {
    public:
        void update(float dt) override;
    };
} // namespace Graphics

#endif
