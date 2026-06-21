/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** TeamBox
*/

#ifndef TEAMBOX_HPP_
    #define TEAMBOX_HPP_

    #include <SFML/Graphics.hpp>
    #include <optional>
    #include <unordered_map>
    #include "Init.hpp"
    #include "SelectAi.hpp"
    #include "StateButton.hpp"

namespace Zappy {
    class TeamBox {
    public:
        TeamBox(sf::Font &font, std::string name, const TextureMap &textures,
            const std::map<std::string, std::string> &ais);

        void draw(sf::RenderWindow &win, std::size_t slots);
        std::optional<std::string> event(
            sf::Event &event, sf::Vector2f mousePos);

        void setHeight(float height);

        [[nodiscard]] bool getFill() const
        {
            return _play.getState() == Init::Play;
        }

        [[nodiscard]] std::vector<std::string> getSelected() const;
        [[nodiscard]] float getHeight() const
        {
            return _height;
        }

    private:
        void drawName(sf::RenderWindow &win);
        void drawAvailableSlot(sf::RenderWindow &win, std::size_t slots);

        sf::RectangleShape _rec;
        sf::Text _text;
        sf::Vector2f _pos;
        float _height;
        SfmlUtils::StateButton<Init::TeamState> _play;
        std::map<std::string, SelectAi> _selected;

        std::string _name;

        static constexpr int NAME_SIZE = 18;
        static constexpr int SLOTS = 15;
        static constexpr float SIZE_PLAY_BUTTON = 25;
        static constexpr float START_HEIGHT =
            SIZE_PLAY_BUTTON + Init::BOX_GAP * 2.f;
        static constexpr float HEIGHT =
            Init::TEAM_BUTTON_SIZE_Y + Init::BOX_GAP;
        static constexpr float WIDTH = Init::TEAM_BUTTON_SIZE_X +
            Init::TEAM_BUTTON_SIZE_Y + Init::BOX_GAP * 2.0;
    };
} // namespace Zappy

#endif /* !TEAMBOX_HPP_ */
