/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Text2D.hpp"
#include <iostream>

namespace Graphics {
    void Text2D::draw2D() const
    {
        if (_font)
            ::DrawTextPro((*_font).get(),
                _str.c_str(),
                _position,
                _origin,
                _rotation,
                _fontSize,
                _spacing,
                _color);
        else
            ::DrawTextPro(GetFontDefault(),
                _str.c_str(),
                _position,
                _origin,
                _rotation,
                _fontSize,
                _spacing,
                _color);
    }

    void Text2D::setFont(raylib::Font &font)
    {
        _font = font;
    }

    void Text2D::setStr(std::string str)
    {
        _str = std::move(str);
    }

    void Text2D::setOrigin(Vector2 origin)
    {
        _origin = origin;
    }

    void Text2D::setFontSize(float fontSize)
    {
        _fontSize = fontSize;
    }

    void Text2D::setSpacing(float spacing)
    {
        _spacing = spacing;
    }

    void Text2D::setColor(raylib::Color color)
    {
        _color = color;
    }

    raylib::Vector2 Text2D::getSize() const
    {
        raylib::Vector2 size;
        if (_font)
            size = MeasureTextEx(
                (*_font).get(), _str.c_str(), _fontSize, _spacing);
        else
            size = MeasureTextEx(
                GetFontDefault(), _str.c_str(), _fontSize, _spacing);
        return size;
    }

    void Text2D::drawMultiColorStrs(
        Text2D &text, const std::vector<MultiColor> &strs)
    {
        auto save = text.getPosition();
        auto pos = save;
        for (const auto &[str, color] : strs) {
            text.setPosition(pos);
            text.setColor(color);
            text.setStr(str);
            text.draw2D();
            pos.x += text.getSize().x;
        }
        text.setPosition(save);
    }
} // namespace Graphics
