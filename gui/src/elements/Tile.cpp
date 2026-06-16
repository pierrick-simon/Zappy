/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Tile
*/

#include "Tile.hpp"

namespace Zappy {
    Tile::Tile()
    {
        _resources = INIT_RESOURCES;
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
