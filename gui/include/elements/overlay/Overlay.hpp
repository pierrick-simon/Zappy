/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Overlay
*/

#ifndef OVERLAY_HPP_
    #define OVERLAY_HPP_

    #include <string_view>
    #include "Resources.hpp"

namespace Zappy {
    class Overlay {
    public:
        Overlay();

        Resources resources;

    private:
        Font _font;
    };
} // namespace Zappy

#endif /* !OVERLAY_HPP_ */
