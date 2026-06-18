/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DescriptionBox
*/

#ifndef DESCRIPTIONBOX_HPP_
    #define DESCRIPTIONBOX_HPP_

    #include <SFML/Graphics.hpp>
    #include "Init.hpp"

namespace Zappy {
    class DescriptionBox {
    public:
        DescriptionBox(sf::Font &font, std::string name, std::string text);

        void draw(sf::RenderWindow &win);

        void setHeight(float height)
        {
            _pos.y = height;
        }

        [[nodiscard]] float getHeight() const
        {
            return _height;
        }

    private:
        void drawName(sf::RenderWindow &win);
        void drawDescription(sf::RenderWindow &win);

        sf::RectangleShape _rec;
        sf::Text _text;
        sf::Vector2f _pos;
        float _height;
        std::string _name;
        std::string _description;

        static constexpr int NAME_SIZE = 18;
        static constexpr int TEXT_SIZE = 15;
        static constexpr float TITLE = 25;
        static constexpr float START_HEIGHT = TITLE + Init::BOX_GAP * 2.f;
    };
} // namespace Zappy

#endif /* !DESCRIPTIONBOX_HPP_ */
