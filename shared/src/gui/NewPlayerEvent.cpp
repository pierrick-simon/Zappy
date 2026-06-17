/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** NewPlayerEvent
*/

#include "NewPlayerEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    NewPlayerEvent::NewPlayerEvent(NewPlayer player) :
        GUIEvent(ServerCmd::PNW), _player(std::move(player))
    {
    }

    NewPlayerEvent::NewPlayerEvent() :
        GUIEvent(ServerCmd::PNW)
    {
    }

    std::string NewPlayerEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << "#" << _player.id << " ";
        oss << _player.x << " ";
        oss << _player.y << " ";
        oss << _player.dir << " ";
        oss << _player.level << " ";
        oss << _player.team;
        return oss.str();
    }

    void NewPlayerEvent::retrieve(std::istringstream &stream)
    {
        char hash;
        stream >> hash >> _player.id >> _player.x >> _player.y;
        stream >> _player.dir >> _player.level >> _player.team;
    }
}; // namespace Shared
