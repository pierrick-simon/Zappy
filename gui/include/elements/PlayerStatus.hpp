/*
** EPITECH PROJECT, 2026
** gui
** File description:
** PlayerStatus
*/

#ifndef PLAYERSTATUS_HPP_
    #define PLAYERSTATUS_HPP_

    #include <map>
    #include <string>

namespace Zappy {
    class PlayerStatus {
    public:
        enum class Status { None, Laying, Elevating, Dying };

        static std::string getMsg(Status status);

    private:
        static const std::map<Status, std::string> _status;
    };
} // namespace Zappy

#endif /* !PLAYERSTATUS_HPP_ */
