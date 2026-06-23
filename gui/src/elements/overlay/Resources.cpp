/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Resources
*/

#include "Resources.hpp"
#include "Init.hpp"
#include "graphics/AShadered.hpp"
#include "graphics/IDrawable2D.hpp"
#include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    Resources::Resources(Font &font)
    {
        float i = 0;
        for (auto &[resource, texture] : INIT) {
            _resources.emplace(resource,
                ResourceInfo {font,
                    {i * (Init::RESOURCE_SIZE.x + Init::RESOURCE_GAP) +
                            Init::RESOURCE_GAP,
                        Init::RESOURCE_GAP},
                    texture});
            i++;
        }
    }

    void Resources::update(const std::map<Info::ResourceName, std::size_t> &map,
        const std::map<Info::ResourceName, std::size_t> &players)
    {
        for (auto &[name, resource] : _resources) {
            auto findMap = map.find(name);
            auto findPlayers = players.find(name);
            std::size_t updateMap = 0;
            std::size_t updatePlayers = 0;
            if (findMap != map.end())
                updateMap = findMap->second;
            if (findPlayers != players.end())
                updatePlayers = findPlayers->second;
            resource.update(updateMap, updatePlayers);
        }
    }

    void Resources::draw2D() const
    {
        for (const auto &[_, resource] : _resources)
            resource.draw2D();
    }

    const std::map<Info::ResourceName, ResourceInfo::TextureSize>
        Resources::INIT = {
            {Info::ResourceName::FOOD, {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::LINEMATE,
                {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::DERAUMERE,
                {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::SIBUR, {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::MENDIANE,
                {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::PHIRAS, {"public/houseIcon.png", {500, 400}}},
            {Info::ResourceName::THYSTAME,
                {"public/houseIcon.png", {500, 400}}},
    };
}; // namespace Zappy
