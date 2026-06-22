/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Players
*/

#include "Players.hpp"
#include <iostream>

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

    Player &Players::getPlayer(std::size_t id)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw Player::PlayerNotFoundException(id);
        if (find->second.isDead())
            throw Player::DeadPlayerException(id);
        return find->second;
    }

    std::size_t Players::getNbPlayer()
    {
        return _players.size();
    }

    std::size_t Players::getFirstPlayerId()
    {
        if (_players.empty())
            throw Player::PlayerNotFoundException(0);
        return _players.begin()->first;
    }
} // namespace Zappy
