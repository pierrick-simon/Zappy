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
    #include "End.hpp"
    #include "EventBox.hpp"
    #include "Player2D.hpp"
    #include "Resources.hpp"
    #include "Team.hpp"
    #include "Tile2D.hpp"
    #include "TimeUnit.hpp"

namespace Zappy {
    class Overlay {
    private:
        raylib::Font _font;

    public:
        Overlay(std::map<std::string, raylib::Color> &teams, bool &quit);

        Resources resources;
        ChatBox chatBox;
        EventBox eventBox;
        Player2D player;
        Team team;
        Tile2D tile;
        TimeUnit timeUnit;
        End end;

        static const std::map<Info::ResourceName, ResourceInfo::TextureSize>
            RESOURCES;
    };
} // namespace Zappy

#endif /* !OVERLAY_HPP_ */
