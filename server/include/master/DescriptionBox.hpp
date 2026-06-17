/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DescriptionBox
*/

#ifndef DESCRIPTIONBOX_HPP_
    #define DESCRIPTIONBOX_HPP_

    #include <SFML/Graphics.hpp>

namespace Zappy {
    class DescriptionBox {
    public:
        DescriptionBox(sf::Font &font, std::string name, std::string text);

        void draw(sf::RenderWindow &win);

        void setHeight(float height)
        {
            _pos.y = height;
        }

    private:
        void drawName(sf::RenderWindow &win);
        void drawDescription(sf::RenderWindow &win);

        sf::RectangleShape _rec;
        sf::Text _text;
        sf::Vector2f _pos;
        std::string _name;
        std::string _description;

        static constexpr int NAME_SIZE = 18;
        static constexpr int TEXT_SIZE = 15;
    };
} // namespace Zappy

#endif /* !DESCRIPTIONBOX_HPP_ */
