/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** ResourceEvent
*/

#ifndef RESOURCEEVENT_HPP
    #define RESOURCEEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class ResourceEvent : public GUIEvent {
    public:
        ResourceEvent(const Command &command, std::size_t id, std::size_t nb);
        ResourceEvent(const Command &command);

        void retrieve(std::istringstream stream) override;

        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }
        [[nodiscard]] std::size_t getNb() const
        {
            return _nb;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _id;
        std::size_t _nb;
    };
} // namespace Shared

#endif
