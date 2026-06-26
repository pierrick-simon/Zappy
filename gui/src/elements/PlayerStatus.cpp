/*
** EPITECH PROJECT, 2026
** gui
** File description:
** PlayerStatus
*/

#include "PlayerStatus.hpp"

namespace Zappy {
    std::string PlayerStatus::getMsg(Status status)
    {
        return _status.at(status);
    }

    const std::map<PlayerStatus::Status, std::string> PlayerStatus::_status = {
        {Status::NONE, "None"},
        {Status::LAYING, "Laying"},
        {Status::ELEVATING, "Elevating"},
        {Status::DYING, "Dying"},
        {Status::ROTATING, "Rotating"},
        {Status::WALKING, "Walking"},
    };
} // namespace Zappy
