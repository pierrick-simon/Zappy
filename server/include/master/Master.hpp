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
    #include "Client.hpp"
    #include "Process.hpp"

namespace Zappy {
    class Master {
    public:
        Master(int port, Clients &clients,
            std::unordered_map<std::string, std::size_t> &teams);

        bool update();

    private:
        void event();
        void addGui();
        void handleResize(sf::Event event);

        sf::RenderWindow _window;
        sf::View _view;
        sf::Font _font;
        sf::RectangleShape _rec;

        int _port;
        Shared::Process _process;

        Clients &_clients;
        std::unordered_map<std::string, std::size_t> &_teams;

        static constexpr std::string_view IP = "127.0.0.1";
        static constexpr std::string_view AI_EXEC = "./zapy_ai";
        static constexpr std::string_view GUI_EXEC = "./zappy_gui";

        static constexpr std::string_view FONT = "public/Font.ttf";

        static constexpr unsigned int WINDOW_SIZE_X = 800;
        static constexpr unsigned int WINDOW_SIZE_Y = 600;
        static constexpr unsigned int WINDOW_BITS = 32;
        static constexpr std::size_t FPS = 120;
        static inline const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 75);
    };
} // namespace Zappy

#endif /* !MASTER_HPP_ */
