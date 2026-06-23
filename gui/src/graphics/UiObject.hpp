/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef UIOBJECT_HPP
    #define UIOBJECT_HPP
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/IUpdatable.hpp"
    #include "graphics/Transformable2D.hpp"

namespace Graphics {

    class UiObject : public IDrawable2D,
                     public IUpdatable,
                     public Transformable2D {
    public:
        void update(float dt) override;
    };

} // namespace Graphics

#endif
