/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Overlay
*/

#include "Overlay.hpp"
#include "Init.hpp"

namespace Zappy {
    Overlay::Overlay(std::unordered_map<std::string, Color> &teams) :
        _font(LoadFont(Init::FONT_PATH.data())),
        resources(_font),
        chatBox(_font, teams),
        eventBox(_font, teams),
        player(_font, teams)
    {
    }

    const std::map<Info::ResourceName, ResourceInfo::TextureSize>
        Overlay::RESOURCES = {
            {Info::ResourceName::Food, {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::Linemate,
                {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::Deraumere,
                {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::Sibur, {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::Mendiane,
                {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::Phiras, {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::Thystame,
                {"public/houseIcon.png", {500, 400}}},
    };
} // namespace Zappy
