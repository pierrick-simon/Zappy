/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** SelectAi
*/

#ifndef SELECTAI_HPP_
    #define SELECTAI_HPP_

    #include <SFML/Graphics.hpp>
    #include "Init.hpp"
    #include "PressButton.hpp"
    #include "StateButton.hpp"

namespace Zappy {
    class SelectAi {
    public:
        SelectAi(sf::Font &font, std::string name, const TextureMap &textures,
            sf::Vector2f pos);

        void draw(sf::RenderWindow &win);
        bool event(sf::Event &event, sf::Vector2f mousePos);
        void setHeight(float height);

        [[nodiscard]] bool getCheck() const
        {
            return _check.getState() == Init::Check;
        }

    private:
        sf::Vector2f _pos;
        SfmlUtils::PressButton _press;
        SfmlUtils::StateButton<Init::TeamState> _check;

        static constexpr int TEXT_SIZE = 15;
    };
} // namespace Zappy

#endif /* !SELECTAI_HPP_ */
