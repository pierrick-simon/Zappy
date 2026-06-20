/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Box2D
*/

#include "Box2D.hpp"

namespace Graphics {
    void Box2D::setBorderSize(float size)
    {
        _borderSize = size;
        update();
    }

    void Box2D::setBorderColor(Color color)
    {
        _borderColor = color;
    }

    void Box2D::setColor(Color color)
    {
        _color = color;
    }

    void Box2D::setSize(Vector2 size)
    {
        _size = size;
        update();
    }

    void Box2D::setPos(Vector2 pos)
    {
        _pos = pos;
        update();
    }

    void Box2D::setRound(float round)
    {
        _round = round;
    }

    void Box2D::setSegement(int segment)
    {
        _segment = segment;
    }

    void Box2D::update()
    {
        _box.SetSize(_size);
        _box.SetPosition(_pos);
        _border.SetSize(
            {_size.x + _borderSize * 2.f, _size.y + _borderSize * 2.f});
        _border.SetPosition({_pos.x - _borderSize, _pos.y - _borderSize});
    }

    void Box2D::draw2D() const
    {
        if (_borderSize > 0.f)
            _border.DrawRounded(_round, _segment, _borderColor);
        _box.DrawRounded(_round, _segment, _color);
    }
} // namespace Graphics
