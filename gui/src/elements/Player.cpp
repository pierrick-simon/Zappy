/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Player
*/

#include "Player.hpp"
#include "Utils.hpp"

namespace Zappy {
    Player::Player(
        Shared::NewPlayerEvent::NewPlayer player, std::ofstream &logFile) :
        _id(player.id),
        _x(player.x),
        _y(player.y),
        _dir(Info::getDirection(player.dir)),
        _level(player.level),
        _team(std::move(player.team)),
        _logFile(logFile)
    {
        Shared::Utils::logMsg(_logFile,
            "Player [" + std::to_string(_id) + "] joined the " + _team +
                " team.");
        _inventory.emplace(Info::ResourceName::Food, 0);
        _inventory.emplace(Info::ResourceName::Linemate, 0);
        _inventory.emplace(Info::ResourceName::Deraumere, 0);
        _inventory.emplace(Info::ResourceName::Sibur, 0);
        _inventory.emplace(Info::ResourceName::Mendiane, 0);
        _inventory.emplace(Info::ResourceName::Phiras, 0);
        _inventory.emplace(Info::ResourceName::Thystame, 0);
    }

    Player::~Player()
    {
        Shared::Utils::logMsg(
            _logFile, "Player [" + std::to_string(_id) + "] died.");
    }

    void Player::move(std::size_t x, std::size_t y, Info::Direction dir)
    {
        _x = x;
        _y = y;
        _dir = dir;
    }

    void Player::setLevel(std::size_t level)
    {
        _level = level;
    }

    void Player::setInventory(const std::vector<std::size_t> &inventory)
    {
        auto iter = _inventory.begin();
        for (auto resource : inventory) {
            if (iter == _inventory.end())
                break;
            iter->second = resource;
            iter++;
        }
    }

    void Player::setIncantate(bool incantate)
    {
        _incantate = incantate;
    }

    void Player::setFork(bool fork)
    {
        _fork = fork;
    }

    std::size_t Player::getTile(std::size_t width) const
    {
        return _y * width + _x;
    }
} // namespace Zappy
