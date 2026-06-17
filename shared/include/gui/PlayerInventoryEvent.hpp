/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** PlayerInventoryEvent
*/

#ifndef PLAYERINVENTORYEVENT_HPP
    #define PLAYERINVENTORYEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class PlayerInventoryEvent : public GUIEvent {
    public:
        PlayerInventoryEvent(std::size_t id, std::size_t x, std::size_t y,
            const std::vector<std::size_t> &resources);
        PlayerInventoryEvent();

        void retrieve(std::istringstream &stream) override;

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
        [[nodiscard]] std::vector<std::size_t> getResources() const
        {
            return _resources;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _id;
        std::size_t _x;
        std::size_t _y;
        std::vector<std::size_t> _resources;
    };
} // namespace Shared

#endif
