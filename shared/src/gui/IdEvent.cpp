/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** IdEvent
*/

#include "IdEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    IdEvent::IdEvent(const Command &command, std::size_t id) :
        GUIEvent(command), _id(id)
    {
    }

    IdEvent::IdEvent(const Command &command) :
        GUIEvent(command), _id(0)
    {
    }

    std::string IdEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << "#" << _id;
        return oss.str();
    }

    void IdEvent::retrieve(std::istringstream &stream)
    {
        char hash;
        stream >> hash >> _id;
    }
}; // namespace Shared
