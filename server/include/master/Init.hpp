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
        static inline const sf::Color PALEGREY = sf::Color(200, 200, 200);

        static constexpr float BOX_GAP = 5;
        static constexpr unsigned int TOOLBAR_SIZE_Y = 40;
        static constexpr int TITLE_SIZE = 22;
        static constexpr float AI_BOX_X = WINDOW_SIZE_X / 3.0f - BOX_GAP * 1.5f;
        static constexpr float AI_BOX_Y = WINDOW_SIZE_Y - TOOLBAR_SIZE_Y;
        static constexpr float DESC_BOX_X = AI_BOX_X - BOX_GAP * 2.0f;
        static constexpr float DESC_BOX_Y = (AI_BOX_Y - BOX_GAP) / 5.0f;

        static constexpr float SCROLL = 30.f;
    };
} // namespace Zappy

#endif /* !Init_HPP_ */
