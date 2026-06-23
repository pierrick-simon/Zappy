/*
** EPITECH PROJECT, 2026
** gui
** File description:
** ChatBox
*/

#ifndef CHATBOX_HPP_
    #define CHATBOX_HPP_

    #include <map>
    #include <vector>
    #include "Init.hpp"
    #include "TextBox.hpp"

namespace Zappy {
    class ChatBox : public TextBox {
    public:
        ChatBox(Font &font, std::map<std::string, Color> &teams);

    private:
        static constexpr std::size_t MAX_LINE = 24;
        static constexpr float FONT_SIZE = 20;
        static constexpr float WIDTH = 300;
    };
} // namespace Zappy

#endif /* !CHATBOX_HPP_ */
