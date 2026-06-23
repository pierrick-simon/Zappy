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

    std::map<Info::ResourceName, std::size_t> Tile::getResources() const
    {
        std::map<Info::ResourceName, std::size_t> map;
        for (const auto &[resource, queue] : _resources)
            map.emplace(resource, queue.size());
        return map;
    }

    const std::map<Info::ResourceName, std::queue<Resource>>
        Tile::INIT_RESOURCES = {
            {Info::ResourceName::FOOD, {}},
            {Info::ResourceName::LINEMATE, {}},
            {Info::ResourceName::DERAUMERE, {}},
            {Info::ResourceName::SIBUR, {}},
            {Info::ResourceName::MENDIANE, {}},
            {Info::ResourceName::PHIRAS, {}},
            {Info::ResourceName::THYSTAME, {}},
    };
} // namespace Zappy
