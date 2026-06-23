/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Players
*/

#include "Players.hpp"
#include <iostream>
#include <ranges>

#include "graphics/AShadered.hpp"

namespace Zappy {
    Players::Players(std::ofstream &logFile) :
        _logFile(logFile)
    {
        this->loadAnimations();
    }

    bool Players::addPlayer(const Shared::NewPlayerEvent::NewPlayer &player)
    {
        bool value = false;
        if (!_players.contains(player.id)) {
            _players.try_emplace(player.id,
                player,
                _logFile,
                this->_model,
                this->_modelAnimation);
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
} // namespace Zappy
