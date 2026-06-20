/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Overlay
*/

#ifndef OVERLAY_HPP_
    #define OVERLAY_HPP_

    #include <string_view>
    #include "ChatBox.hpp"
    #include "Resources.hpp"

namespace Zappy {
    class Overlay {
    public:
        Overlay(std::unordered_map<std::string, Color> &teams);

        Resources resources;
        ChatBox chatBox;

    private:
        Font _font;
    };
} // namespace Zappy

#endif /* !OVERLAY_HPP_ */
