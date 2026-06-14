/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** BroadcastEvent
*/

#include "BroadcastEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    BroadcastEvent::BroadcastEvent(std::size_t id, std::string msg) :
        GUIEvent(ServerCmd::PBC), _id(id), _msg(std::move(msg))
    {
    }

    BroadcastEvent::BroadcastEvent() :
        GUIEvent(ServerCmd::PBC), _id(0)
    {
    }

    std::string BroadcastEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << "#" << _id << " ";
        oss << _msg;
        return oss.str();
    }

    void BroadcastEvent::retrieve(std::istringstream &stream)
    {
        char hash;
        stream >> hash >> _id;
        _msg = stream.str();
    }
}; // namespace Shared
