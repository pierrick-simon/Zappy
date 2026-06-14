/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** TileInfoEvent
*/

#ifndef TILEINFOEVENT_HPP
    #define TILEINFOEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class TileInfoEvent : public GUIEvent {
    public:
        TileInfoEvent(std::size_t x, std::size_t y,
            const std::vector<std::size_t> &resources);
        TileInfoEvent();

        void retrieve(std::istringstream &stream) override;

        [[nodiscard]] std::size_t getX() const
        {
            return _x;
        }
        [[nodiscard]] std::size_t getY() const
        {
            return _y;
        }
        [[nodiscard]] std::vector<std::size_t> getResources() const
        {
            return _resources;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _x;
        std::size_t _y;
        std::vector<std::size_t> _resources;
    };
} // namespace Shared

#endif
