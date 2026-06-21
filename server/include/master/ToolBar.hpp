/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** ToolBar
*/

#ifndef TOOLBAR_HPP_
    #define TOOLBAR_HPP_

    #include <SFML/Graphics.hpp>
    #include <string_view>
    #include "AddProcess.hpp"
    #include "Client.hpp"
    #include "Init.hpp"
    #include "StateButton.hpp"

namespace Zappy {
    class ToolBar {
    public:
        enum PlaySate { Play, Pause, Show, None };

        ToolBar(
            sf::Font &font, int port, AddProcess &process, Clients &clients);

        void draw(sf::RenderWindow &win);
        void event(sf::Event &event, sf::Vector2f mousePos);

        [[nodiscard]] bool getPlaying() const
        {
            return _playing;
        }

    private:
        int _port;
        sf::Text _text;
        sf::RectangleShape _rec;
        sf::Texture _playTexture;
        sf::Texture _pauseTexture;
        sf::Texture _showTexture;

        bool _playing = false;
        SfmlUtils::StateButton<PlaySate> _play;
        SfmlUtils::StateButton<PlaySate> _show;

        std::string _ip;

        Clients &_clients;
        AddProcess &_process;

        static constexpr std::string_view PORT = "Port: ";
        static constexpr std::string_view IP = "IP: ";
        static constexpr std::string_view PLAY = "public/play.png";
        static constexpr std::string_view PAUSE = "public/pause.png";
        static constexpr std::string_view SHOW = "public/show.png";
        static constexpr float GAP = 2.0f;
        static constexpr float SIZE_PLAY_BUTTON =
            Init::TOOLBAR_SIZE_Y - 2 * GAP;
    };
} // namespace Zappy

#endif /* !TOOLBAR_HPP_ */
