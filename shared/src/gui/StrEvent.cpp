/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** StrEvent
*/

#include "StrEvent.hpp"
#include "GUICommunication.hpp"

namespace ServerCmd = Shared::GUICommunication::Server;

namespace Shared {
    StrEvent::StrEvent(const Command &command, std::string str) :
        GUIEvent(command), _str(std::move(str))
    {
    }

    StrEvent::StrEvent(const Command &command) :
        GUIEvent(command)
    {
    }

    std::string StrEvent::getMsg() const
    {
        return _str;
    }

    void StrEvent::retrieve(std::istringstream &stream)
    {
        _str = stream.str();
        std::getline(stream, _str);
        _str.erase(0, _str.find_first_not_of(" \n\r\t"));
        _str.erase(_str.find_last_not_of(" \n\r\t") + 1);
    }
}; // namespace Shared
