/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** PressButton
*/

#include "PressButton.hpp"

namespace SfmlUtils {
    PressButton::PressButton(sf::Font &font, unsigned int textSize,
        std::string str, sf::Color color) :
        AButton(ButtonType::PRESSED),
        _textSize(textSize),
        _str(std::move(str)),
        _color(color)
    {
        _text.setFont(font);
        _text.setCharacterSize(textSize);
        _text.setFillColor(sf::Color::Black);
        _text.setCharacterSize(_textSize);
        _text.setString(_str);
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.f, rc.top + rc.height / 2.f);
        _text.setPosition(_pos.x + _size.x / 2.f, _pos.y + _size.y / 2.f);
        _rec.setSize(_size);
        _rec.setOutlineColor(sf::Color::Black);
        _rec.setOutlineThickness(2);
        _rec.setPosition(_pos);
        setBound(_rec.getGlobalBounds());
    }

    void PressButton::draw(sf::RenderWindow &win)
    {
        if (_hover)
            _rec.setFillColor(SfmlUtils::colorOffset(_color, -50));
        else
            _rec.setFillColor(_color);
        win.draw(_rec);
        win.draw(_text);
    }

    void PressButton::func()
    {
        _push = !_push;
    }

    void PressButton::setPos(sf::Vector2f pos)
    {
        _pos = pos;
        _rec.setPosition(_pos);
        _text.setPosition(_pos.x + _size.x / 2.f, _pos.y + _size.y / 2.f);
        setBound(_rec.getGlobalBounds());
    }

    void PressButton::setSize(sf::Vector2f size)
    {
        _size = size;
        _text.setPosition(_pos.x + _size.x / 2.f, _pos.y + _size.y / 2.f);
        _rec.setSize(_size);
        setBound(_rec.getGlobalBounds());
    }
} // namespace SfmlUtils
