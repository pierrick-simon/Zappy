/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AiDescription
*/

#include "AiDescription.hpp"
#include "Init.hpp"

namespace Zappy {
    AiDescription::AiDescription(
        sf::Font &font, const std::map<std::string, std::string> &ais)
    {
        _rec.setSize({Init::AI_BOX_X, Init::AI_BOX_Y});
        _rec.setPosition({Init::BOX_GAP, Init::TOOLBAR_SIZE_Y});
        _rec.setFillColor(Init::BACKGROUND_COLOR);
        for (const auto &[name, text] : ais)
            _descriptions.emplace_back(font, name, text);
        float height = 0;
        for (auto &desc : _descriptions) {
            desc.setHeight(
                Init::TOOLBAR_SIZE_Y + Init::BOX_GAP + height - _scroll);
            height += desc.getHeight() + Init::BOX_GAP;
        }
        _totalHeight = height;
    }

    void AiDescription::draw(sf::RenderWindow &win)
    {
        win.draw(_rec);
        for (auto &desc : _descriptions)
            desc.draw(win);
    }

    void AiDescription::event(sf::Event &event, sf::Vector2f mousePos)
    {
        if (_rec.getGlobalBounds().contains(mousePos) &&
            event.type == sf::Event::MouseWheelMoved) {
            _scroll -= float(event.mouseWheel.delta) * Init::SCROLL;
            auto max = _totalHeight - Init::AI_BOX_Y + Init::BOX_GAP;
            if (max <= 0)
                _scroll = 0;
            else
                _scroll = std::clamp(_scroll, 0.f, max);
            float height = 0;
            for (std::size_t i = 0; i < _descriptions.size(); i++) {
                _descriptions[i].setHeight(Init::TOOLBAR_SIZE_Y +
                    Init::BOX_GAP + float(i) * Init::BOX_GAP + height -
                    _scroll);
                height += _descriptions[i].getHeight();
            }
        }
    }
}; // namespace Zappy
