/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Overlay
*/

#include "Overlay.hpp"

namespace Zappy {
    Overlay::Overlay(std::unordered_map<std::string, Color> &teams) :
        _font(LoadFont("public/Font.ttf")),
        resources(_font),
        chatBox(_font, teams)
    {
    }
} // namespace Zappy
