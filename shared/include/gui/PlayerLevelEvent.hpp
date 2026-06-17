/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** PlayerLevelEvent
*/

#ifndef PLAYERLEVEL_HPP
    #define PLAYERLEVEL_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class PlayerLevelEvent : public GUIEvent {
    public:
        PlayerLevelEvent(std::size_t id, std::size_t level);
        PlayerLevelEvent();

        void retrieve(std::istringstream &stream) override;

        [[nodiscard]] std::size_t getId() const
        {
            return _id;
        }
        [[nodiscard]] std::size_t getLevel() const
        {
            return _level;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _id;
        std::size_t _level;
    };
} // namespace Shared

#endif
