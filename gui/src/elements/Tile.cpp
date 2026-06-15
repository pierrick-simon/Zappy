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
        _resources.insert({Info::ResourceName::Food, {}});
        _resources.insert({Info::ResourceName::Linemate, {}});
        _resources.insert({Info::ResourceName::Deraumere, {}});
        _resources.insert({Info::ResourceName::Sibur, {}});
        _resources.insert({Info::ResourceName::Mendiane, {}});
        _resources.insert({Info::ResourceName::Phiras, {}});
        _resources.insert({Info::ResourceName::Thystame, {}});
    }

    void Tile::updateResource(
        std::queue<Resource> &resource, std::size_t nb, Info::ResourceName type)
    {
        while (resource.size() != nb) {
            if (resource.size() < nb)
                resource.push(Resource {type});
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
} // namespace Zappy
