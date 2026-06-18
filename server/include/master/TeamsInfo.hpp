/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** TeamsInfo
*/

#ifndef TEAMSINFO_HPP_
    #define TEAMSINFO_HPP_

    #include <SFML/Graphics.hpp>
    #include <chrono>
    #include <unordered_map>
    #include <vector>
    #include "AddProcess.hpp"
    #include "Client.hpp"
    #include "TeamBox.hpp"
    #include "Utils.hpp"

namespace Zappy {
    class TeamsInfo {
    public:
        TeamsInfo(sf::Font &font, const std::map<std::string, std::string> &ais,
            AddProcess &process,
            std::unordered_map<std::string, std::size_t> &teams);

        void draw(sf::RenderWindow &win);
        void event(sf::Event &event, sf::Vector2f mousePos);

    private:
        struct Team {
            TeamBox box;
            std::chrono::milliseconds sleep;
        };

        Shared::Clock _clock;
        sf::RectangleShape _rec;
        sf::Texture _playTexture;
        sf::Texture _pauseTexture;
        sf::Texture _emptyTexture;
        sf::Texture _checkTexture;
        std::unordered_map<std::string, Team> _teamsBox;
        float _scroll = 0.f;
        float _totalHeight;

        AddProcess &_process;
        std::unordered_map<std::string, std::size_t> &_teams;

        static constexpr std::string_view PLAY = "public/play.png";
        static constexpr std::string_view PAUSE = "public/pause.png";
        static constexpr std::string_view CHECK = "public/checkBoxCheck.png";
        static constexpr std::string_view EMPTY = "public/checkBoxEmpty.png";
        static constexpr std::chrono::milliseconds SLEEP =
            std::chrono::milliseconds(100);
    };
} // namespace Zappy

#endif /* !TEAMSINFO_HPP_ */
