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
        NewPlayerEvent(std::size_t id, std::size_t x, std::size_t y,
            std::size_t dir, std::string team);
        NewPlayerEvent();

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
        [[nodiscard]] std::size_t getLevel() const
        {
            return _level;
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
        std::size_t _dir;
        std::size_t _level;
        std::string _team;
    };
} // namespace Shared

#endif
