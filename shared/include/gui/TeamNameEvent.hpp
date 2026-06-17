/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** TeamNameEvent
*/

#ifndef TEAMNAME_HPP
    #define TEAMNAME_HPP

    #include <string>
    #include "GUIEvent.hpp"

namespace Shared {
    class TeamNameEvent : public GUIEvent {
    public:
        TeamNameEvent(std::string team);
        TeamNameEvent();

        void retrieve(std::istringstream &stream) override;

        [[nodiscard]] std::string getTeam() const
        {
            return _team;
        }

    protected:
        [[nodiscard]] std::string getMsg() const override;

    private:
        std::string _team;
    };
} // namespace Shared

#endif
