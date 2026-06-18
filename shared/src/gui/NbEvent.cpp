/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** NbEvent
*/

#include "NbEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    NbEvent::NbEvent(const Command &command, std::size_t nb) :
        GUIEvent(command), _nb(nb)
    {
    }

    NbEvent::NbEvent(const Command &command) :
        GUIEvent(command), _nb(0)
    {
    }

    std::string NbEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << _nb;
        return oss.str();
    }

    void NbEvent::retrieve(std::istringstream stream)
    {
        stream >> _nb;
    }
}; // namespace Shared
