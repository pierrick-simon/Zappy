/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Info
*/

#ifndef INIT_HPP_
    #define INIT_HPP_

    #include "graphics/AShadered.hpp"

namespace Zappy {
    class Init {
    public:
        static constexpr Color GOLD_RICH = {212, 160, 23, 255};
        static constexpr Color DARK_PINEWOOD = {28, 52, 32, 255};

        static constexpr float BORDER_SIZE = 3.f;
        static constexpr float BORDER_ROUND = 0.1f;

        static constexpr Vector2 RESOURCE_SIZE = {125, 30};
        static constexpr float RESOURCE_GAP = 10.f;
    };
} // namespace Zappy

#endif /* !INFO_HPP_ */
