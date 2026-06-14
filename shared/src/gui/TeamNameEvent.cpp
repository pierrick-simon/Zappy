/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** TeamNameEvent
*/

#include "TeamNameEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    TeamNameEvent::TeamNameEvent(std::string team) :
        GUIEvent(ServerCmd::TNA), _team(std::move(team))
    {
    }

    TeamNameEvent::TeamNameEvent() :
        GUIEvent(ServerCmd::TNA)
    {
    }

    std::string TeamNameEvent::getMsg() const
    {
        return _team;
    }

    void TeamNameEvent::retrieve(std::istringstream &stream)
    {
        stream >> _team;
    }
}; // namespace Shared
