/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** EndIncantationEvent
*/

#ifndef ENDINCANTATIONEVENT_HPP
    #define ENDINCANTATIONEVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class EndIncantationEvent : public GUIEvent {
    public:
        EndIncantationEvent(std::size_t x, std::size_t y, bool result);
        EndIncantationEvent();

        void retrieve(std::istringstream &stream) override;

        [[nodiscard]] std::size_t getX() const
        {
            return _x;
        }
        [[nodiscard]] std::size_t getY() const
        {
            return _y;
        }
        [[nodiscard]] bool getResult() const
        {
            return _result;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::size_t _x;
        std::size_t _y;
        bool _result;
    };
} // namespace Shared

#endif
