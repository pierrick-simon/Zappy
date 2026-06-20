/*
** EPITECH PROJECT, 2026
** gui
** File description:
** EventBox
*/

#ifndef EVENTBOX_HPP_
    #define EVENTBOX_HPP_

    #include <unordered_map>
    #include <vector>
    #include "Init.hpp"
    #include "TextBox.hpp"

namespace Zappy {
    class EventBox : public TextBox {
    public:
        EventBox(Font &font, std::unordered_map<std::string, Color> &teams);

    private:
        static constexpr std::size_t MAX_LINE = 10;
        static constexpr float FONT_SIZE = 20;
        static constexpr float WIDTH = 200;
    };
} // namespace Zappy

#endif /* !EVENTBOX_HPP_ */
