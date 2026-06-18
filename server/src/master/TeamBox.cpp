/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** TeamBox
*/

#include "TeamBox.hpp"
#include "Init.hpp"

namespace Zappy {
    TeamBox::TeamBox(sf::Font &font, std::string name,
        const TextureMap &textures,
        const std::map<std::string, std::string> &ais) :
        _play({{Init::Pause, textures.at(Init::Play), sf::Color::Red},
            {Init::Play, textures.at(Init::Pause), sf::Color::Green}}),
        _name(std::move(name))
    {
        _pos.x = Init::BOX_GAP * 3.0f + Init::AI_BOX_X;
        _text.setFont(font);
        _text.setFillColor(sf::Color::Black);
        _rec.setFillColor(Init::PALEGREY);
        _height = START_HEIGHT +
            HEIGHT * (float(ais.size() + 1) / Init::NB_BUTTON) +
            Init::BOX_GAP * 2.f;
        _rec.setSize({Init::INFO_BOX_X, _height});
        _play.setSize({SIZE_PLAY_BUTTON, SIZE_PLAY_BUTTON});
        std::size_t i = 0;
        for (auto &[name, _] : ais) {
            auto column = i % Init::NB_BUTTON;
            auto row = i / Init::NB_BUTTON;
            auto x = Init::BOX_GAP * 1.5f + WIDTH * float(column) + _pos.x;
            auto y = START_HEIGHT + HEIGHT * float(row) + _pos.y;
            _selected.insert({name, {font, name, textures, {x, y}}});
            i++;
        }
    }

    void TeamBox::setHeight(float height)
    {
        _pos.y = height;
        _play.setPos(
            {Init::WINDOW_SIZE_X - Init::BOX_GAP * 3.f - SIZE_PLAY_BUTTON,
                _pos.y + Init::BOX_GAP});
        std::size_t i = 0;
        for (auto &[_, select] : _selected) {
            auto row = i / Init::NB_BUTTON;
            auto y = START_HEIGHT + HEIGHT * float(row) + _pos.y;
            select.setHeight(y);
            i++;
        }
    }

    void TeamBox::draw(sf::RenderWindow &win, std::size_t slots)
    {
        _rec.setPosition(_pos);
        win.draw(_rec);
        drawName(win);
        _play.draw(win);
        drawAvailableSlot(win, slots);
        for (auto &[_, select] : _selected)
            select.draw(win);
    }

    void TeamBox::drawName(sf::RenderWindow &win)
    {
        _text.setCharacterSize(NAME_SIZE);
        _text.setStyle(sf::Text::Style::Bold);
        _text.setString(_name);
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left, rc.top + rc.height / 2.f);
        _text.setPosition({_pos.x + Init::BOX_GAP,
            _pos.y + Init::BOX_GAP + SIZE_PLAY_BUTTON / 2.f});
        win.draw(_text);
    }

    void TeamBox::drawAvailableSlot(sf::RenderWindow &win, std::size_t slots)
    {
        _text.setCharacterSize(SLOTS);
        _text.setStyle(sf::Text::Style::Regular);
        _text.setString("Available Slot(s): " + std::to_string(slots));
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.f, rc.top + rc.height / 2.f);
        _text.setPosition({_pos.x + Init::BOX_GAP + Init::INFO_BOX_X / 2.f,
            _pos.y + Init::BOX_GAP + SIZE_PLAY_BUTTON / 2.f});
        win.draw(_text);
    }

    std::vector<std::string> TeamBox::getSelected() const
    {
        std::vector<std::string> selected;
        for (auto &[name, select] : _selected) {
            if (select.getCheck())
                selected.emplace_back(name);
        }
        return selected;
    }

    std::optional<std::string> TeamBox::event(
        sf::Event &event, sf::Vector2f mousePos)
    {
        _play.click(mousePos, event);
        std::optional<std::string> click;
        for (auto &[name, select] : _selected) {
            if (select.event(event, mousePos))
                click = name;
        }
        return click;
    }

} // namespace Zappy
