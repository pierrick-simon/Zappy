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
    NewPlayerEvent::NewPlayerEvent(std::size_t id, std::size_t x, std::size_t y,
        std::size_t dir, std::string team) :
        GUIEvent(ServerCmd::PNW),
        _id(id),
        _x(x),
        _y(y),
        _dir(dir),
        _level(1),
        _team(std::move(team))
    {
    }

    NewPlayerEvent::NewPlayerEvent() :
        GUIEvent(ServerCmd::PNW), _id(0), _x(0), _y(0), _dir(0), _level(1)
    {
    }

    std::string NewPlayerEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << "#" << _id << " ";
        oss << _x << " ";
        oss << _y << " ";
        oss << _dir << " ";
        oss << _level << " ";
        oss << _team;
        return oss.str();
    }

    void NewPlayerEvent::retrieve(std::istringstream &stream)
    {
        char hash;
        stream >> hash >> _id >> _x >> _y >> _dir >> _level >> _team;
    }
}; // namespace Shared
