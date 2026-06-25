/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Tile
*/

#include "Tile.hpp"
#include "Utils.hpp"

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
        std::deque<Resource> &resource, std::size_t nb, Info::ResourceName type)
    {
        while (resource.size() != nb) {
            Vector2 range((TILE_SIZE.x / 2.0) - TILE_PADDING * TILE_SIZE.x,
                (TILE_SIZE.y / 2.0) - TILE_PADDING * TILE_SIZE.y);
            if (resource.size() < nb)
                resource.emplace_back(type,
                    Vector3(Shared::Utils::fRandRange(-range.x, range.x),
                        0,
                        Shared::Utils::fRandRange(-range.y, range.y)),
                    Shared::Utils::fRandRange(
                        1.0 - SCALE_MODIF_RANGE, 1.0 + SCALE_MODIF_RANGE));
            else
                resource.pop_front();
        }
    }

    const std::map<Info::ResourceName, std::deque<Resource>> &
    Tile::getResources() const
    {
        return _resources;
    }

    std::map<Info::ResourceName, std::size_t> Tile::getNbResources() const
    {
        std::map<Info::ResourceName, std::size_t> map;
        for (const auto &[resource, deque] : _resources)
            map.emplace(resource, deque.size());
        return map;
    }

    const std::map<Info::ResourceName, std::deque<Resource>>
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
