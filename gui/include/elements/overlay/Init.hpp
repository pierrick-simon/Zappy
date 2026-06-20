/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Info
*/

#ifndef INIT_HPP_
    #define INIT_HPP_

    #include <string_view>
    #include "graphics/AShadered.hpp"

namespace Zappy {
    class Init {
    public:
        static constexpr std::string_view FONT_PATH = "public/Font.ttf";

        static constexpr Color GOLD_RICH = {212, 160, 23, 255};
        static constexpr Color DARK_PINEWOOD = {28, 52, 32, 255};
        static constexpr Color BLUE_THROUGH = {0, 0, 139, 128};

        static constexpr float BORDER_SIZE = 3.f;
        static constexpr float BORDER_ROUND = 0.1f;
        static constexpr float LETTER_SPACING = 2;
        static constexpr float GAP = 10.f;

        static constexpr Vector2 RESOURCE_SIZE = {125, 40};
        static constexpr float RESOURCE_ICON = 26;
        static constexpr Vector2 RESOURCE_ICON_POS = {18, 18};
        static constexpr float RESOURCE_GAP = GAP;

        static constexpr Vector2 INCANTATION_START_POS = {
            GAP, RESOURCE_SIZE.y * 3.f + RESOURCE_GAP * 2.f};
        static constexpr Vector2 INCANTATION_SIZE = {220, 140};
        static constexpr float INCANTATION_GAP = GAP;
        static constexpr std::size_t INCANTATION_MAX_DISPLAY = 4;

        static constexpr Vector2 EVENT_START_POS = {
            GAP, INCANTATION_START_POS.y + (INCANTATION_SIZE.y + GAP) * 4.f};
    };
} // namespace Zappy

#endif /* !INFO_HPP_ */
