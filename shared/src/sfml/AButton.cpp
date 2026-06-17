/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** AButton
*/

#include "AButton.hpp"

namespace SfmlUtils {
    bool AButton::isHover(sf::Vector2f mousePos)
    {
        _hover = _bound.contains(mousePos);
        return _hover;
    }

    void AButton::click(sf::Vector2f mousePos, sf::Event event)
    {
        if (isHover(mousePos) && event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
            func();
    }
} // namespace SfmlUtils
