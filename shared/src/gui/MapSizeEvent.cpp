/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** MapSizeEvent
*/

#include "MapSizeEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    MapSizeEvent::MapSizeEvent(std::size_t x, std::size_t y) :
        GUIEvent(ServerCmd::MSZ), _x(x), _y(y)
    {
    }

    MapSizeEvent::MapSizeEvent() :
        GUIEvent(ServerCmd::MSZ), _x(0), _y(0)
    {
    }

    std::string MapSizeEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << _x << " ";
        oss << _y;
        return oss.str();
    }

    void MapSizeEvent::retrieve(std::istringstream stream)
    {
        stream >> _x >> _y;
    }
}; // namespace Shared
