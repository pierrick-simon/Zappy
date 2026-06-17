/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Master
*/

#ifndef MASTER_HPP_
    #define MASTER_HPP_

    #include <SFML/Graphics.hpp>
    #include <string_view>
    #include "AddProcess.hpp"
    #include "AiDescription.hpp"
    #include "Client.hpp"
    #include "ToolBar.hpp"

namespace Zappy {
    class Master {
    public:
        Master(int port, Clients &clients,
            std::unordered_map<std::string, std::size_t> &teams);

        bool update();

        [[nodiscard]] bool getPlaying() const
        {
            return _toolBar.getPlaying();
        }

    private:
        void event();
        void handleResize(sf::Event event);

        sf::RenderWindow _window;
        sf::View _view;
        sf::Font _font;
        sf::RectangleShape _rec;

        AddProcess _process;
        ToolBar _toolBar;
        AiDescription _aiDescription;

        Clients &_clients;
        std::unordered_map<std::string, std::size_t> &_teams;

        static const std::unordered_map<std::string, std::string> _ais;

        static constexpr std::string_view FONT = "public/Font.ttf";
        static constexpr std::string_view TITLE = "Zappy Master Server";
    };
} // namespace Zappy

#endif /* !MASTER_HPP_ */
