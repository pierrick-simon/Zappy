/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** EggLaidEvent
*/

#ifndef EGGLAIDEVENT_HPP
    #define EGGLAIDEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class EggLaidEvent : public GUIEvent {
    public:
        EggLaidEvent(std::size_t eggId, std::size_t playerId, std::size_t x,
            std::size_t y);
        EggLaidEvent();

        void retrieve(std::istringstream stream) override;

        [[nodiscard]] std::size_t getEggId() const
        {
            return _eggId;
        }
        [[nodiscard]] std::size_t getPlayerId() const
        {
            return _playerId;
        }
        [[nodiscard]] std::size_t getX() const
        {
            return _x;
        }
        [[nodiscard]] std::size_t getY() const
        {
            return _y;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _eggId;
        std::size_t _playerId;
        std::size_t _x;
        std::size_t _y;
    };
} // namespace Shared

#endif
