/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** PlayerPositionEvent
*/

#ifndef PLAYERPOSITION_HPP
    #define PLAYERPOSITION_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class PlayerPositionEvent : public GUIEvent {
    public:
        PlayerPositionEvent(
            std::size_t id, std::size_t x, std::size_t y, std::size_t dir);
        PlayerPositionEvent();

        void retrieve(std::istringstream &stream) override;

        [[nodiscard]] std::size_t getX() const
        {
            return _x;
        }
        [[nodiscard]] std::size_t getY() const
        {
            return _y;
        }
        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }
        [[nodiscard]] std::size_t getDir() const
        {
            return _dir;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _id;
        std::size_t _x;
        std::size_t _y;
        std::size_t _dir;
    };
} // namespace Shared

#endif
