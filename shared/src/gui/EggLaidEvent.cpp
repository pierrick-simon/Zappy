/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** EggLaidEvent
*/

#include "EggLaidEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    EggLaidEvent::EggLaidEvent(
        std::size_t eggId, std::size_t playerId, std::size_t x, std::size_t y) :
        GUIEvent(ServerCmd::ENW),
        _eggId(eggId),
        _playerId(playerId),
        _x(x),
        _y(y)
    {
    }

    EggLaidEvent::EggLaidEvent() :
        GUIEvent(ServerCmd::ENW), _eggId(0), _playerId(0), _x(0), _y(0)
    {
    }

    std::string EggLaidEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << "#" << _eggId << " ";
        oss << "#" << _playerId << " ";
        oss << _x << " ";
        oss << _y;
        return oss.str();
    }

    void EggLaidEvent::retrieve(std::istringstream stream)
    {
        char hash;
        stream >> hash >> _eggId >> hash >> _playerId >> _x >> _y;
    }
}; // namespace Shared
