/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Overlay
*/

#include "Overlay.hpp"

namespace Zappy {
    Overlay::Overlay() :
        _font(LoadFont("public/Font.ttf")), resources(_font)
    {
    }
} // namespace Zappy
