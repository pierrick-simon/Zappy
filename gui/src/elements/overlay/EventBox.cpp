/*
** EPITECH PROJECT, 2026
** gui
** File description:
** EventBox
*/

#include "EventBox.hpp"
#include "Init.hpp"

namespace Zappy {
    EventBox::EventBox(Font &font, std::map<std::string, Color> &teams) :
        TextBox(font, teams, Init::BLUE_THROUGH)
    {

        auto y = float(GetScreenHeight());
        auto maxLine =
            (y - Init::EVENT_START_POS.y - Init::GAP * 2.f) / FONT_SIZE;
        setMaxLine(std::size_t(maxLine));
        setFontSize(FONT_SIZE);
        setWidth(WIDTH);
        setPos(Init::EVENT_START_POS);
    }
} // namespace Zappy
