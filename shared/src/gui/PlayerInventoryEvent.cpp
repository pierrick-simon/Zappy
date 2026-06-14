/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** PlayerInventoryEvent
*/

#include "PlayerInventoryEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    PlayerInventoryEvent::PlayerInventoryEvent(
        std::size_t id, const std::vector<std::size_t> &resources) :
        GUIEvent(ServerCmd::PIN), _id(id), _resources(resources)
    {
    }

    PlayerInventoryEvent::PlayerInventoryEvent() :
        GUIEvent(ServerCmd::PIN), _id(0), _resources(NB_RESOURCE)
    {
    }

    std::string PlayerInventoryEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << "#" << _id;
        for (auto resource : _resources)
            oss << " " << resource;
        return oss.str();
    }

    void PlayerInventoryEvent::retrieve(std::istringstream &stream)
    {
        char hash;
        stream >> hash >> _id;
        for (auto &resource : _resources)
            stream >> resource;
    }
}; // namespace Shared
