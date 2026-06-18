/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Init
*/

#ifndef INIT_HPP_
    #define INIT_HPP_

    #include <SFML/Graphics.hpp>
    #include <memory>
    #include <unordered_map>

namespace Zappy {
    class Init {
    public:
        enum TeamState { Play, Pause, Empty, Check };

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

        static constexpr float TEAM_BOX_X =
            WINDOW_SIZE_X / 3.0f * 2.f - BOX_GAP * 1.5f;
        static constexpr float TEAM_BOX_Y = WINDOW_SIZE_Y - TOOLBAR_SIZE_Y;
        static constexpr float INFO_BOX_X = TEAM_BOX_X - BOX_GAP * 2.0f;
        static constexpr float INFO_BOX_Y = (TEAM_BOX_Y - BOX_GAP) / 4.0f;

        static constexpr std::size_t NB_BUTTON = 3;
        static constexpr float TEAM_BUTTON_TOTAL =
            (INFO_BOX_X - BOX_GAP * 2.f) / NB_BUTTON - BOX_GAP;
        static constexpr float TEAM_BUTTON_SIZE_Y = 25;
        static constexpr float TEAM_BUTTON_SIZE_X =
            TEAM_BUTTON_TOTAL - TEAM_BUTTON_SIZE_Y - BOX_GAP;

        static constexpr float SCROLL = 30.f;
    };

    using TextureMap = std::unordered_map<Init::TeamState,
        std::reference_wrapper<sf::Texture>>;
} // namespace Zappy

#endif /* !Init_HPP_ */
