/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** TileInfoEvent
*/

#include "TileInfoEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    TileInfoEvent::TileInfoEvent(std::size_t x, std::size_t y,
        const std::vector<std::size_t> &resources) :
        GUIEvent(ServerCmd::BCT), _x(x), _y(y), _resources(resources)
    {
    }

    TileInfoEvent::TileInfoEvent() :
        GUIEvent(ServerCmd::BCT), _x(0), _y(0), _resources(NB_RESOURCE)
    {
    }

    std::string TileInfoEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << _x << " ";
        oss << _y;
        for (auto resource : _resources)
            oss << " " << resource;
        return oss.str();
    }

    void TileInfoEvent::retrieve(std::istringstream &stream)
    {
        stream >> _x >> _y;
        for (auto &resource : _resources)
            stream >> resource;
    }
}; // namespace Shared
