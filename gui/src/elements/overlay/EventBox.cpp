/*
** EPITECH PROJECT, 2026
** gui
** File description:
** EventBox
*/

#include "EventBox.hpp"
#include "Init.hpp"

namespace Zappy {
    EventBox::EventBox(
        Font &font, std::unordered_map<std::string, Color> &teams) :
        TextBox(font, teams, Init::BLUE_THROUGH)
    {

        auto x = float(GetScreenWidth());
        auto y = float(GetScreenHeight());
        setMaxLine(MAX_LINE);
        setFontSize(FONT_SIZE);
        setWidth(WIDTH);
        setPos({Init::GAP, y - getHeight() - Init::GAP});
    }
} // namespace Zappy
