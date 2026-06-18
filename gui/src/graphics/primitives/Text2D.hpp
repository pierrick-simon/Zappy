/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef TEXT2D_HPP
    #define TEXT2D_HPP
    #include <Text.hpp>

    #include "graphics/UiObject.hpp"

namespace Graphics {

    class Text2D : public raylib::Text, public UiObject {
    public:
        using Text::Text;
        void draw2D() const override;
    };

} // namespace Graphics

#endif
