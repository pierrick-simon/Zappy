/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** EggEvent
*/

#ifndef EGGEVENT_HPP
    #define EGGEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class EggEvent : public GUIEvent {
    public:
        EggEvent(
            std::size_t id, std::size_t x, std::size_t y, std::string team);
        EggEvent();

        void retrieve(std::istringstream stream) override;

        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }

        [[nodiscard]] std::size_t getX() const
        {
            return _x;
        }

        [[nodiscard]] std::size_t getY() const
        {
            return _y;
        }

        [[nodiscard]] std::string getTeam() const
        {
            return _team;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _id;
        std::size_t _x;
        std::size_t _y;
        std::string _team;
    };
} // namespace Shared

#endif
