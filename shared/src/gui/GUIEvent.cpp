/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUIEvent
*/

#include "GUIEvent.hpp"
#include "Connect.hpp"

namespace Shared {
    void GUIEvent::send(const std::vector<int> &fds)
    {
        auto msg = _command.getStr() + " " + getMsg() + "\n";
        for (const auto &fd : fds)
            Connect::send(fd, msg);
    }
} // namespace Shared
