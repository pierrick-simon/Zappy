/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** StartIncantationEvent
*/

#include "StartIncantationEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    StartIncantationEvent::StartIncantationEvent(std::size_t x, std::size_t y,
        std::size_t level, const std::vector<std::size_t> &ids) :
        GUIEvent(ServerCmd::PIC), _x(x), _y(y), _level(level), _ids(ids)
    {
    }

    StartIncantationEvent::StartIncantationEvent() :
        GUIEvent(ServerCmd::PIC), _x(0), _y(0), _level(0)
    {
    }

    std::string StartIncantationEvent::getMsg() const
    {
        std::ostringstream oss;
        oss << _x << " ";
        oss << _y << " ";
        oss << _level;
        for (auto id : _ids)
            oss << " #" << id;
        return oss.str();
    }

    void StartIncantationEvent::retrieve(std::istringstream &stream)
    {
        _ids.clear();
        stream >> _x >> _y >> _level;
        while (stream.eof()) {
            char hash;
            std::size_t tmp;
            stream >> hash >> tmp;
            _ids.push_back(tmp);
        }
    }
}; // namespace Shared
