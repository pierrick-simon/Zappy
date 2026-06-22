/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef RECTANGLE_2D_HPP
    #define RECTANGLE_2D_HPP
    #include <Rectangle.hpp>

    #include "graphics/UiObject.hpp"

namespace Graphics {

    class Rectangle2D : public raylib::Rectangle, public UiObject {
    public:
        using Rectangle::Rectangle;
        void draw2D() const override;
        Color &getColor();
        [[nodiscard]] const Color &getColor() const;

    private:
        Color _color = BLACK;
    };

} // namespace Graphics

#endif
