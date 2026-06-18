/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** SelectAi
*/

#include "SelectAi.hpp"

namespace Zappy {
    SelectAi::SelectAi(sf::Font &font, std::string name,
        const TextureMap &textures, sf::Vector2f pos) :
        _pos(pos),
        _press(font, TEXT_SIZE, std::move(name)),
        _check({{Init::Empty, textures.at(Init::Empty)},
            {Init::Check, textures.at(Init::Check)}})
    {
        _press.setSize({Init::TEAM_BUTTON_SIZE_X, Init::TEAM_BUTTON_SIZE_Y});
        _press.setPos(_pos);
        _check.setSize({Init::TEAM_BUTTON_SIZE_Y, Init::TEAM_BUTTON_SIZE_Y});
        _check.setPos(
            {_pos.x + Init::TEAM_BUTTON_SIZE_X + Init::BOX_GAP, _pos.y});
    }

    void SelectAi::setHeight(float height)
    {
        _pos.y = height;
        _press.setPos(_pos);
        _check.setPos(
            {_pos.x + Init::TEAM_BUTTON_SIZE_X + Init::BOX_GAP, _pos.y});
    }

    void SelectAi::draw(sf::RenderWindow &win)
    {
        _check.draw(win);
        _press.draw(win);
    }

    bool SelectAi::event(sf::Event &event, sf::Vector2f mousePos)
    {
        _check.click(mousePos, event);
        _press.click(mousePos, event);
        bool value = false;
        if (_press.getPush()) {
            _press.reset();
            value = true;
        }
        return value;
    }
} // namespace Zappy
