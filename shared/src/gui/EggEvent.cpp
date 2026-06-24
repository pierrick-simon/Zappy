/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** EggEvent
*/

#include "EggEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    EggEvent::EggEvent(
        std::size_t id, std::size_t x, std::size_t y, std::string team) :
        GUIEvent(ServerCmd::EGG), _id(id), _x(x), _y(y), _team(std::move(team))
    {
    }

    EggEvent::EggEvent() :
        GUIEvent(ServerCmd::EGG), _id(0), _x(0), _y(0)
    {
    }

    std::string EggEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << "#" << _id << " ";
        oss << _x << " ";
        oss << _y << " ";
        oss << _team;
        return oss.str();
    }

    void EggEvent::retrieve(std::istringstream stream)
    {
        char hash;
        stream >> hash >> _id >> _x >> _y >> _team;
    }
}; // namespace Shared
