/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** NbEvent
*/

#ifndef NBEVENT_HPP
    #define NBEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class NbEvent : public GUIEvent {
    public:
        NbEvent(const Command &command, std::size_t nb);
        NbEvent(const Command &command);

        void retrieve(std::istringstream stream) override;

        [[nodiscard]] std::size_t getNb() const
        {
            return _nb;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _nb;
    };
} // namespace Shared

#endif
