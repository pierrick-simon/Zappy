/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** MapSizeEvent
*/

#ifndef MAPSIZEEVENT_HPP
    #define MAPSIZEEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class MapSizeEvent : public GUIEvent {
    public:
        MapSizeEvent(std::size_t x, std::size_t y);
        MapSizeEvent();

        void retrieve(std::istringstream &stream) override;

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
        std::size_t _x;
        std::size_t _y;
    };
} // namespace Shared

#endif
