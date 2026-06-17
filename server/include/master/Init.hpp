/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Init
*/

#ifndef INIT_HPP_
    #define INIT_HPP_

    #include <SFML/Graphics.hpp>

namespace Zappy {
    class Init {
    public:
        static constexpr unsigned int WINDOW_SIZE_X = 800;
        static constexpr unsigned int WINDOW_SIZE_Y = 600;
        static constexpr unsigned int WINDOW_BITS = 32;
        static constexpr std::size_t FPS = 120;

        static inline const sf::Color BACKGROUND_COLOR = sf::Color(50, 50, 75);
        static inline const sf::Color LIGHTGREY = sf::Color(150, 150, 150);

        static constexpr unsigned int TOOLBAR_SIZE_Y = 40;
        static constexpr int TITLE_SIZE = 22;
    };
} // namespace Zappy

#endif /* !Init_HPP_ */
