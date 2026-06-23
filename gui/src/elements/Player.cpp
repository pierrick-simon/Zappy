/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Player
*/

#include "Player.hpp"

#include <iostream>

#include "Utils.hpp"

namespace Zappy {
    Player::Player(const Shared::NewPlayerEvent::NewPlayer &player,
        std::ofstream &logFile, raylib::Model &model,
        std::vector<::ModelAnimation> &modelAnimation) :
        _id(player.id),
        _x(player.x),
        _y(player.y),
        _level(player.level),
        _dir(Info::getDirection(player.dir)),
        _team(player.team),
        _logFile(logFile),
        _status(PlayerStatus::Status::NONE),
        _model(model),
        _modelAnimation(modelAnimation)
    {
        Shared::Utils::logMsg(_logFile,
            "Player [" + std::to_string(_id) + "] joined the " + _team +
                " team.");
        _inventory = Info::INIT_RESOUCES;
        this->setAnimationIndex(0);
    }

    void Player::move(std::size_t x, std::size_t y, Info::Direction dir)
    {
        _x = x;
        _y = y;
        _dir = dir;
        this->setRotation(
            DIRECTION_TO_QUATERNION[static_cast<std::size_t>(dir)]);
        _eject = false;
    }

    void Player::addLevel()
    {
        _level++;
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
        if (_incantate)
            _status = PlayerStatus::Status::ELEVATING;
        else
            _status = PlayerStatus::Status::NONE;
    }

    void Player::setFork(bool fork)
    {
        _fork = fork;
        if (_fork)
            _status = PlayerStatus::Status::LAYING;
        else
            _status = PlayerStatus::Status::NONE;
    }

    void Player::setEject(bool eject)
    {
        _eject = eject;
    }

    std::size_t Player::getTile(std::size_t width) const
    {
        return _y * width + _x;
    }

    void Player::draw3D() const
    {
        this->_model.UpdateAnimation(this->getCurrentAnimation(),
            static_cast<float>(this->_animationFrame));
        auto [axis, angle] = this->getRotation().ToAxisAngle();
        this->_model.Draw(
            this->_position, axis, Maths::RadToDeg(angle), this->_scale);
    }

    void Player::update(float dt)
    {
        this->_frameTime += dt;
        float normalized =
            std::fmod(this->_frameTime, this->_animationDuration);
        this->_animationFrame =
            static_cast<std::size_t>(normalized * ANIMATIONS_FPS);
    }

    void Player::setAnimationIndex(size_t index)
    {
        this->_currentAnimationIndex = index;
        this->_animationDuration =
            static_cast<float>(this->getCurrentAnimation().keyframeCount) /
            ANIMATIONS_FPS;
    }

    const ModelAnimation &Player::getCurrentAnimation() const
    {
        return this->_modelAnimation[this->_currentAnimationIndex];
    }

    ModelAnimation &Player::getCurrentAnimation()
    {
        return this->_modelAnimation[this->_currentAnimationIndex];
    }

    void Player::died()
    {
        _incantate = false;
        _fork = false;
        _dead = true;
        Shared::Utils::logMsg(
            _logFile, "Player [" + std::to_string(_id) + "] died.");
        _status = PlayerStatus::Status::DYING;
    }

    void Player::takeResource(Info::ResourceName resource)
    {
        _inventory[resource]++;
    }

    void Player::setResource(Info::ResourceName resource)
    {
        auto find = _inventory.find(resource);
        if (find != _inventory.end() && find->second != 0)
            find->second--;
    }

    Player2D::PlayerInfo Player::getPlayerInfo() const
    {
        return Player2D::PlayerInfo {
            _id, _team, _level, _x, _y, _status, _inventory};
    }
} // namespace Zappy
