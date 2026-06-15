/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** NewPlayerEvent
*/

#ifndef NEWPLAYEREVENT_HPP
    #define NEWPLAYEREVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class NewPlayerEvent : public GUIEvent {
    public:
        struct NewPlayer {
            std::size_t id;
            std::size_t x;
            std::size_t y;
            std::size_t dir;
            std::size_t level;
            std::string team;
        };

        NewPlayerEvent(NewPlayer);
        NewPlayerEvent();

        void retrieve(std::istringstream &stream) override;

        [[nodiscard]] NewPlayer getPlayer() const
        {
            return _player;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        NewPlayer _player;
    };
} // namespace Shared

#endif
