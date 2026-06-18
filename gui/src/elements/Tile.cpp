/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Tile
*/

#include "Tile.hpp"

#include <iostream>

namespace Zappy {
    Tile::Tile()
    {
        this->_resources = INIT_RESOURCES;
    }

    void Tile::updateTile(const std::vector<std::size_t> &resources)
    {
        auto iter = _resources.begin();
        for (auto resource : resources) {
            if (iter == _resources.end())
                break;
            updateResource(iter->second, resource, iter->first);
            iter++;
        }
    }

    void Tile::updateResource(
        std::queue<Resource> &resource, std::size_t nb, Info::ResourceName type)
    {
        while (resource.size() != nb) {
            if (resource.size() < nb)
                resource.emplace(type);
            else
                resource.pop();
        }
    }

    const std::map<Info::ResourceName, std::queue<Resource>>
        Tile::INIT_RESOURCES = {
            {Info::ResourceName::Food, {}},
            {Info::ResourceName::Linemate, {}},
            {Info::ResourceName::Deraumere, {}},
            {Info::ResourceName::Sibur, {}},
            {Info::ResourceName::Mendiane, {}},
            {Info::ResourceName::Phiras, {}},
            {Info::ResourceName::Thystame, {}},
    };
} // namespace Zappy
