/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** StartIncantationEvent
*/

#ifndef STARTINCANTATIONEVENT_HPP
    #define STARTINCANTATIONEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class StartIncantationEvent : public GUIEvent {
    public:
        StartIncantationEvent(std::size_t x, std::size_t y, std::size_t level,
            const std::vector<std::size_t> &ids);
        StartIncantationEvent();

        void retrieve(std::istringstream stream) override;

        [[nodiscard]] std::size_t getX() const
        {
            return _x;
        }
        [[nodiscard]] std::size_t getY() const
        {
            return _y;
        }
        [[nodiscard]] std::size_t getLevel() const
        {
            return _level;
        }
        [[nodiscard]] std::vector<std::size_t> getIds() const
        {
            return _ids;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _x;
        std::size_t _y;
        std::size_t _level;
        std::vector<std::size_t> _ids;
    };
} // namespace Shared

#endif
