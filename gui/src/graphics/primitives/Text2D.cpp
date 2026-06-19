/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Text2D.hpp"

namespace Graphics {
    void Text2D::draw2D() const
    {
        Font font;
        if (_font)
            DrawTextPro((*_font).get(),
                _str.c_str(),
                _pos,
                _origin,
                _rotation,
                _fontSize,
                _spacing,
                _color);
        else
            DrawTextPro(GetFontDefault(),
                _str.c_str(),
                _pos,
                _origin,
                _rotation,
                _fontSize,
                _spacing,
                _color);
    }

    void Text2D::setFont(Font &font)
    {
        _font = font;
    }

    void Text2D::setStr(std::string str)
    {
        _str = std::move(str);
    }

    void Text2D::setPos(Vector2 pos)
    {
        _pos = pos;
    }

    void Text2D::setOrigin(Vector2 origin)
    {
        _origin = origin;
    }

    void Text2D::setRotation(float rotation)
    {
        _rotation = rotation;
    }

    void Text2D::setFontSize(float fontSize)
    {
        _fontSize = fontSize;
    }

    void Text2D::setSpacing(float spacing)
    {
        _spacing = spacing;
    }

    void Text2D::setColor(Color color)
    {
        _color = color;
    }

    Vector2 Text2D::getSize() const
    {
        Vector2 size;
        if (_font)
            size = MeasureTextEx(
                (*_font).get(), _str.c_str(), _fontSize, _spacing);
        else
            size = MeasureTextEx(
                GetFontDefault(), _str.c_str(), _fontSize, _spacing);
        return size;
    }
} // namespace Graphics
