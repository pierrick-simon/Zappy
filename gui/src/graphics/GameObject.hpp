/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef GAMEOBJECT_HPP
    #define GAMEOBJECT_HPP

    #include "../../include/graphics/IObject.hpp"
    #include "Transformable3D.hpp"
    #include "graphics/IDrawable.hpp"
    #include "graphics/IUpdatable.hpp"

namespace Graphics {
    class GameObject : public Transformable3D,
                       public IDrawable,
                       public IUpdatable,
                       public IObject {
    public:
        void update(float dt) override;
    };
} // namespace Graphics

#endif
