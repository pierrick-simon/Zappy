/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Overlay
*/

#include "Overlay.hpp"
#include "Init.hpp"

namespace Zappy {
    Overlay::Overlay(std::map<std::string, raylib::Color> &teams, bool &quit) :
        font(Init::FONT_PATH.data()),
        resources(font),
        chatBox(font, teams),
        eventBox(font, teams),
        player(font, teams),
        team(font, teams),
        tile(font),
        timeUnit(font),
        end(font, teams, quit)
    {
    }

    const std::map<Info::ResourceName, ResourceInfo::TextureSize>
        Overlay::RESOURCES = {
            {Info::ResourceName::FOOD, {"public/heart.png", {1080, 1080}}},
            {Info::ResourceName::LINEMATE, {"public/stone1.png", {1080, 1080}}},
            {Info::ResourceName::DERAUMERE,
                {"public/stone2.png", {1080, 1080}}},
            {Info::ResourceName::SIBUR, {"public/stone3.png", {1080, 1080}}},
            {Info::ResourceName::MENDIANE, {"public/stone4.png", {1080, 1080}}},
            {Info::ResourceName::PHIRAS, {"public/stone5.png", {1080, 1080}}},
            {Info::ResourceName::THYSTAME, {"public/stone6.png", {1080, 1080}}},
    };
} // namespace Zappy
