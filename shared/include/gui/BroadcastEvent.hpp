/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** BroadcastEvent
*/

#ifndef BROADCASTEVENT_HPP
    #define BROADCASTEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class BroadcastEvent : public GUIEvent {
    public:
        BroadcastEvent(std::size_t id, std::string msg);
        BroadcastEvent();

        void retrieve(std::istringstream stream) override;

        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }

        [[nodiscard]] std::string getText() const
        {
            return _msg;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _id;
        std::string _msg;
    };
} // namespace Shared

#endif
