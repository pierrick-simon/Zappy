/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Overlay
*/

#include "Overlay.hpp"
#include "Init.hpp"

namespace Zappy {
    Overlay::Overlay(std::map<std::string, Color> &teams) :
        _font(LoadFont(Init::FONT_PATH.data())),
        resources(_font),
        chatBox(_font, teams),
        eventBox(_font, teams),
        player(_font, teams),
        team(_font, teams)
    {
    }

    const std::map<Info::ResourceName, ResourceInfo::TextureSize>
        Overlay::RESOURCES = {
            {Info::ResourceName::Food, {"public/heart.png", {1080, 1080}}},
            {Info::ResourceName::Linemate, {"public/stone1.png", {1080, 1080}}},
            {Info::ResourceName::Deraumere,
                {"public/stone2.png", {1080, 1080}}},
            {Info::ResourceName::Sibur, {"public/stone3.png", {1080, 1080}}},
            {Info::ResourceName::Mendiane, {"public/stone4.png", {1080, 1080}}},
            {Info::ResourceName::Phiras, {"public/stone5.png", {1080, 1080}}},
            {Info::ResourceName::Thystame, {"public/stone6.png", {1080, 1080}}},
    };
} // namespace Zappy
