/*
** EPITECH PROJECT, 2026
** gui
** File description:
** EventBox
*/

#ifndef EVENTBOX_HPP_
    #define EVENTBOX_HPP_

    #include <map>
    #include <vector>
    #include "Init.hpp"
    #include "TextBox.hpp"

namespace Zappy {
    class EventBox : public TextBox {
    public:
        EventBox(Font &font, std::map<std::string, Color> &teams);

    private:
        static constexpr float FONT_SIZE = 18;
        static constexpr float WIDTH = 200;
    };
} // namespace Zappy

#endif /* !EVENTBOX_HPP_ */
