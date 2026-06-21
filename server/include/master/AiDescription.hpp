/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AiDescription
*/

#ifndef AIDESCRIPTION_HPP_
    #define AIDESCRIPTION_HPP_

    #include <SFML/Graphics.hpp>
    #include <unordered_map>
    #include <vector>
    #include "DescriptionBox.hpp"

namespace Zappy {
    class AiDescription {
    public:
        AiDescription(
            sf::Font &font, const std::map<std::string, std::string> &ais);

        void draw(sf::RenderWindow &win);
        void event(sf::Event &event, sf::Vector2f mousePos);

    private:
        sf::RectangleShape _rec;
        std::vector<DescriptionBox> _descriptions;
        float _scroll = 0.f;
        float _totalHeight;
    };
} // namespace Zappy

#endif /* !AIDESCRIPTION_HPP_ */
