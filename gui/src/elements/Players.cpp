/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Players
*/

#include "Players.hpp"
#include <iostream>
#include <ranges>

#include "Map.hpp"
#include "graphics/AShadered.hpp"

namespace Zappy {
    Players::Players(std::ofstream &logFile) :
        _logFile(logFile)
    {
        this->loadAnimations();
    }

    std::optional<std::reference_wrapper<Player>> Players::addPlayer(
        const Shared::NewPlayerEvent::NewPlayer &player)
    {
        std::optional<std::reference_wrapper<Player>> value;
        if (!_players.contains(player.id)) {
            auto iter = _players.try_emplace(player.id,
                player,
                _logFile,
                this->_model,
                this->_modelAnimation);
            value = iter.first->second;
        }
        return value;
    }

    void Players::initPos(std::size_t width, std::size_t height)
    {
        raylib::Vector2 mapSize = raylib::Vector2 {static_cast<float>(width),
                                      static_cast<float>(height)} *
            Map::TILE_SIZE;
        for (auto &[_, player] : _players) {
            raylib::Vector2 center =
                raylib::Vector2 {static_cast<float>(player.getX()),
                    static_cast<float>(player.getY())} *
                    Map::TILE_SIZE -
                mapSize / 2.0f;
            player.initPos(center);
        }
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
        for (const auto &player : this->_players | std::ranges::views::values)
            player.draw3D();
    }

    void Players::update(float dt)
    {
        for (auto &player : this->_players | std::ranges::views::values)
            player.update(dt);
    }

    void Players::setShader(Graphics::Shader &shader)
    {
        AShadered::setShader(shader);
        this->_model.materials[STONE_MAT].shader = this->getShader().asShader();
        this->_model.materials[GLOWING_MAT].shader =
            this->getShader().asShader();
    }

    void Players::loadAnimations()
    {
        int count = 0;
        ::ModelAnimation *modelAnimations =
            ::LoadModelAnimations(PLAYER_MODEL_PATH.c_str(), &count);

        this->_modelAnimation = {modelAnimations, modelAnimations + count};
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

    std::array<std::size_t, Team::NB_LEVEL> Players::getTeamPlayers(
        const std::string &team) const
    {
        std::array<std::size_t, Team::NB_LEVEL> levels = {};
        for (const auto &[_, player] : _players) {
            if (!player.isDead() && player.getTeam() == team &&
                player.getLevel() <= Team::NB_LEVEL && player.getLevel() != 0)
                levels[player.getLevel() - 1]++;
        }
        return levels;
    }

    std::size_t Players::getNbTilePlayers(
        std::size_t tile, std::size_t width) const
    {
        std::size_t nb = 0;
        for (const auto &[_, player] : _players) {
            if (!player.isDead() && player.getTile(width) == tile)
                nb++;
        }
        return nb;
    }

    std::optional<std::size_t> Players::getNextPlayer(
        InfoBox::Action dir, std::size_t player) const
    {
        std::optional<std::size_t> value;
        auto find = _players.find(player);

        if (find == _players.end() || dir == InfoBox::Action::NONE) {
            if (!_players.empty() && dir == InfoBox::Action::NONE)
                value = player;
            if (!_players.empty() && dir != InfoBox::Action::NONE)
                value = _players.begin()->first;
        } else if (dir == InfoBox::Action::LEFT) {
            if (find == _players.begin())
                value = _players.rbegin()->first;
            else
                value = (--find)->first;
        } else {
            if (find == --_players.end())
                value = _players.begin()->first;
            else
                value = (++find)->first;
        }
        return value;
    }
} // namespace Zappy
