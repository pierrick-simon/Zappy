/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef SPRITE_2D_HPP
    #define SPRITE_2D_HPP
    #include <Texture.hpp>

    #include "graphics/UiObject.hpp"

namespace Graphics {

    class Sprite2D : public raylib::Texture, public UiObject {
    public:
        using Texture::Texture;
        void draw2D() const override;
    };
} // namespace Graphics

#endif
