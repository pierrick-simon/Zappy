/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** ResourceEvent
*/

#include "ResourceEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    ResourceEvent::ResourceEvent(
        const Command &command, std::size_t id, std::size_t nb) :
        GUIEvent(command), _id(id), _nb(nb)
    {
    }

    ResourceEvent::ResourceEvent(const Command &command) :
        GUIEvent(command), _id(0), _nb(0)
    {
    }

    std::string ResourceEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << "#" << _id << " ";
        oss << _nb;
        return oss.str();
    }

    void ResourceEvent::retrieve(std::istringstream &stream)
    {
        char hash;
        stream >> hash >> _id >> _nb;
    }
}; // namespace Shared
