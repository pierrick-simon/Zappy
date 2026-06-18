/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** SfmlUtils
*/

#ifndef SFMLUTILS_HPP
    #define SFMLUTILS_HPP

    #include <SFML/Graphics.hpp>
    #include "SharedException.hpp"

namespace SfmlUtils {
    class SfmlUtils {
    public:
        static sf::Color colorOffset(const sf::Color &color, int offset);
        static sf::Font loadFromFile(const std::string &file);
        static sf::Texture loadTextureFromFile(const std::string &file);

        class FileNotFoundException : public Shared::SharedException {
        public:
            FileNotFoundException(const std::string &file) :
                SharedException("File " + file + " not found.") {};
        };
    };
} // namespace SfmlUtils

#endif
