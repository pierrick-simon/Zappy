/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** SfmlUtils
*/

#include "SfmlUtils.hpp"

namespace SfmlUtils {
    sf::Color SfmlUtils::colorOffset(const sf::Color &color, int offset)
    {
        sf::Color update(std::clamp(color.r + offset, 0, 255),
            std::clamp(color.g + offset, 0, 255),
            std::clamp(color.b + offset, 0, 255));
        return update;
    }

    sf::Font SfmlUtils::loadFromFile(const std::string &file)
    {
        sf::Font font;
        if (!font.loadFromFile(file))
            throw FileNotFoundException(file);
        return font;
    }

    sf::Texture SfmlUtils::loadTextureFromFile(const std::string &file)
    {
        sf::Texture texture;
        if (!texture.loadFromFile(file))
            throw FileNotFoundException(file);
        return texture;
    }
} // namespace SfmlUtils
