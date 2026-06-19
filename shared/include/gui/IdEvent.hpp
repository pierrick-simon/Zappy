/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** IdEvent
*/

#ifndef IDEVENT_HPP
    #define IDEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class IdEvent : public GUIEvent {
    public:
        IdEvent(const Command &command, std::size_t id);
        IdEvent(const Command &command);

        void retrieve(std::istringstream stream) override;

        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _id;
    };
} // namespace Shared

#endif
