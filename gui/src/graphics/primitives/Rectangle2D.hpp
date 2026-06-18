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

    class Rectangle2D : public raylib::Rectangle, public UIObject {
    public:
        using Rectangle::Rectangle;
        void draw() const override;
        Color &getColor();
        [[nodiscard]] const Color &getColor() const;

    private:
        Color _color;
    };

} // namespace Graphics

#endif
