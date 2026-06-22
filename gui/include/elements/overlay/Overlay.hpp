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
    #include "EventBox.hpp"
    #include "Player2D.hpp"
    #include "Resources.hpp"
    #include "Team.hpp"
    #include "Tile2D.hpp"

namespace Zappy {
    class Overlay {
    public:
        Overlay(std::map<std::string, Color> &teams);

        Resources resources;
        ChatBox chatBox;
        EventBox eventBox;
        Player2D player;
        Team team;
        Tile2D tile;

        static const std::map<Info::ResourceName, ResourceInfo::TextureSize>
            RESOURCES;

    private:
        Font _font;
    };
} // namespace Zappy

#endif /* !OVERLAY_HPP_ */
