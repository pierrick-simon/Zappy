/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DescriptionBox
*/

#include "DescriptionBox.hpp"
#include "Init.hpp"

namespace Zappy {
    DescriptionBox::DescriptionBox(
        sf::Font &font, std::string name, std::string text) :
        _name(std::move(name)), _description(std::move(text))
    {
        _pos.x = Init::BOX_GAP * 2.0f;
        _text.setFont(font);
        _text.setFillColor(sf::Color::Black);
        _rec.setFillColor(Init::PALEGREY);
        _rec.setSize({Init::DESC_BOX_X, Init::DESC_BOX_Y});
    }

    void DescriptionBox::draw(sf::RenderWindow &win)
    {
        _rec.setPosition(_pos);
        win.draw(_rec);
        drawName(win);
        drawDescription(win);
    }

    void DescriptionBox::drawName(sf::RenderWindow &win)
    {
        _text.setCharacterSize(NAME_SIZE);
        _text.setStyle(sf::Text::Style::Bold);
        _text.setString(_name);
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left, rc.top);
        _text.setPosition({_pos.x + Init::BOX_GAP, _pos.y + Init::BOX_GAP});
        win.draw(_text);
    }

    void DescriptionBox::drawDescription(sf::RenderWindow &win)
    {
        _text.setCharacterSize(TEXT_SIZE);
        _text.setStyle(sf::Text::Style::Regular);
        _text.setString(_description);
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left, rc.top + rc.height / 2.0f);
        _text.setPosition({_pos.x + Init::BOX_GAP,
            _pos.y + (Init::DESC_BOX_Y - NAME_SIZE * 2.f) / 2.f +
                (NAME_SIZE - Init::BOX_GAP) * 2.f});
        win.draw(_text);
    }
}; // namespace Zappy
