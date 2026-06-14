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
    #include "GUICommunication.hpp"

namespace Shared {
    class GUIEvent {
    public:
        GUIEvent(const Command &command) :
            _command(command) {};
        virtual ~GUIEvent() = default;

        void send(const std::vector<int> &fds);
        virtual void retrieve(std::istringstream &stream) = 0;

        [[nodiscard]] std::string getCommand() const
        {
            return _command.getStr();
        }

    protected:
        [[nodiscard]] virtual std::string getMsg() const = 0;
        const Command &_command;

        static constexpr std::size_t NB_RESOURCE = 7;
    };
} // namespace Shared

#endif
