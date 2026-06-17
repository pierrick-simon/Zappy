/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef UIOBJECT_HPP
    #define UIOBJECT_HPP
    #include "graphics/Drawable.hpp"
    #include "graphics/Transformable2D.hpp"

namespace Graphics {

    class UIObject : public Drawable, public Transformable2D {
    public:
        virtual void update(float dt);
    };

} // namespace Graphics

#endif
