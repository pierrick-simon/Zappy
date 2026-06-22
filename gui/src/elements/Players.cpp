/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Players
*/

#include "Players.hpp"
#include <iostream>
#include <ranges>

namespace Zappy {
    Players::Players(std::ofstream &logFile) :
        _logFile(logFile)
    {
    }

    bool Players::addPlayer(const Shared::NewPlayerEvent::NewPlayer &player)
    {
        bool value = false;
        if (!_players.contains(player.id)) {
            _players.try_emplace(player.id, player, _logFile);
            value = true;
        }
        return value;
    }

    void Players::updateTotalResources(
        const std::map<Info::ResourceName, std::size_t> &before,
        std::map<Info::ResourceName, std::size_t> after)
    {
        for (const auto &[resource, nb] : before) {
            auto findAfter = after.find(resource);
            auto findTotal = _totalResources.find(resource);
            if (findTotal == _totalResources.end())
                continue;
            if (findAfter != after.end()) {
                findTotal->second = findTotal->second - nb + findAfter->second;
                after.erase(findAfter);
            } else
                findTotal->second -= nb;
        }
        for (const auto &[resource, nb] : after) {
            auto findTotal = _totalResources.find(resource);
            if (findTotal != _totalResources.end())
                findTotal->second += nb;
            else
                _totalResources.emplace(resource, nb);
        }
    }
    void Players::draw3D() const
    {
        DrawModel(this->_model, {0, 0, 0}, 1, {255, 255, 255, 255});
        for (const auto &player : this->_players | std::ranges::views::values) {
            auto [axis, angle] = player.getRotation().ToAxisAngle();
            DrawModelEx(this->_model,
                player.getPosition(),
                axis,
                angle,
                player.getScale(),
                {255, 255, 255, 255});
            // this->_model.Draw(player.getPosition(), axis, angle,
            // player.getScale());
        }
    }

    Player &Players::getPlayer(std::size_t id)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw Player::PlayerNotFoundException(id);
        if (find->second.isDead())
            throw Player::DeadPlayerException(id);
        return find->second;
    }
} // namespace Zappy
