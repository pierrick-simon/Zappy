/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** PlayerPositionEvent
*/

#include "PlayerPositionEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    PlayerPositionEvent::PlayerPositionEvent(
        std::size_t id, std::size_t x, std::size_t y, std::size_t dir) :
        GUIEvent(ServerCmd::PPO), _id(id), _x(x), _y(y), _dir(dir)
    {
    }

    PlayerPositionEvent::PlayerPositionEvent() :
        GUIEvent(ServerCmd::PPO), _id(0), _x(0), _y(0), _dir(0)
    {
    }

    std::string PlayerPositionEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << "#" << _id << " ";
        oss << _x << " ";
        oss << _y << " ";
        oss << _dir;
        return oss.str();
    }

    void PlayerPositionEvent::retrieve(std::istringstream &stream)
    {
        char hash;
        stream >> hash >> _id >> _x >> _y >> _dir;
    }
}; // namespace Shared
