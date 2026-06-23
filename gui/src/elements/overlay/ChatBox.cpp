/*
** EPITECH PROJECT, 2026
** gui
** File description:
** ChatBox
*/

#include "ChatBox.hpp"
#include "Init.hpp"

namespace Zappy {
    ChatBox::ChatBox(Font &font, std::map<std::string, Color> &teams) :
        TextBox(font, teams, Init::BLUE_THROUGH)
    {

        auto x = float(Init::WINDOW_SIZE_X);
        auto y = float(Init::WINDOW_SIZE_Y);
        setMaxLine(MAX_LINE);
        setFontSize(FONT_SIZE);
        setWidth(WIDTH);
        setPos({x - WIDTH - Init::GAP, y - getHeight() - Init::GAP});
    }
} // namespace Zappy
