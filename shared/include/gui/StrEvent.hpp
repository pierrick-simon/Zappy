/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** StrEvent
*/

#ifndef STREVENT_HPP
    #define STREVENT_HPP

    #include "GUIEvent.hpp"

namespace Shared {
    class StrEvent : public GUIEvent {
    public:
        StrEvent(const Command &command, std::string str);
        StrEvent(const Command &command);

        void retrieve(std::istringstream &stream) override;

        [[nodiscard]] std::string getStr() const
        {
            return _str;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::string _str;
    };
} // namespace Shared

#endif
