/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUIEvent
*/

#ifndef GUIEVENT_HPP
    #define GUIEVENT_HPP

    #include <iomanip>
    #include <sstream>
    #include <vector>

namespace Shared {
    class GUIEvent {
    public:
        virtual ~GUIEvent() = default;
        virtual void send(const std::vector<int> &fds) = 0;
        virtual void retrieve(std::istringstream &stream) = 0;
    };
} // namespace Shared

#endif
