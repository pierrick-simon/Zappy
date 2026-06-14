/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** PlayerLevelEvent
*/

#include "PlayerLevelEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    PlayerLevelEvent::PlayerLevelEvent(std::size_t id, std::size_t level) :
        GUIEvent(ServerCmd::PPO), _id(id), _level(level)
    {
    }

    PlayerLevelEvent::PlayerLevelEvent() :
        GUIEvent(ServerCmd::PPO), _id(0), _level(0)
    {
    }

    std::string PlayerLevelEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << "#" << _id << " ";
        oss << _level;
        return oss.str();
    }

    void PlayerLevelEvent::retrieve(std::istringstream &stream)
    {
        char hash;
        stream >> hash >> _id >> _level;
    }
}; // namespace Shared
