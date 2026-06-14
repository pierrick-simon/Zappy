/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** EndIncantationEvent
*/

#include "EndIncantationEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    EndIncantationEvent::EndIncantationEvent(
        std::size_t x, std::size_t y, bool result) :
        GUIEvent(ServerCmd::PIE), _x(x), _y(y), _result(result)
    {
    }

    EndIncantationEvent::EndIncantationEvent() :
        GUIEvent(ServerCmd::PIE), _x(0), _y(0), _result(false)
    {
    }

    std::string EndIncantationEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << _x << " ";
        oss << _y << " ";
        oss << _result;
        return oss.str();
    }

    void EndIncantationEvent::retrieve(std::istringstream &stream)
    {
        stream >> _x >> _y >> _result;
    }
}; // namespace Shared
