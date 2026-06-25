/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Player
*/

#include "Player.hpp"

#include <iostream>

#include "Map.hpp"
#include "Players.hpp"
#include "Utils.hpp"

namespace Zappy {
    Player::Player(const Shared::NewPlayerEvent::NewPlayer &player,
        std::ofstream &logFile, raylib::Model &model,
        std::vector<::ModelAnimation> &modelAnimation) :
        _id(player.id),
        _x(player.x),
        _y(player.y),
        _targetX(player.x),
        _targetY(player.y),
        _level(player.level),
        _dir(Info::getDirection(player.dir)),
        _targetDir(Info::getDirection(player.dir)),
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
        this->setAnimation(PlayerAnimations::IDLE);
    }

    void Player::initPos(raylib::Vector2 pos)
    {
        _position = raylib::Vector3 {pos.x, 0, pos.y};
        this->_startPos = this->_position;
        this->_targetPos = this->_position;
    }

    void Player::move(std::size_t x, std::size_t y, raylib::Vector2 target,
        Info::Direction dir)
    {
        if (x != _x || y != _y) {
            _startPos = this->_position;
            _targetPos = raylib::Vector3 {target.x, 0, target.y};
            _targetX = x;
            _targetY = y;
            _walking = true;
            _timer = WALKING_TIME;
        }
        if (dir != _dir) {
            _targetDir = dir;
            this->_startRotation = this->getRotation();
            this->_targetRotation =
                DIRECTION_TO_QUATERNION[static_cast<std::size_t>(_targetDir)];
            _rotate = true;
            _timer = ROTATE_TIME;
        }
        _eject = false;
    }

    void Player::teleport(
        std::size_t x, std::size_t y, std::size_t width, std::size_t height)
    {
        raylib::Vector2 mapSize = raylib::Vector2 {static_cast<float>(width),
                                      static_cast<float>(height)} *
            Tile::TILE_SIZE;
        raylib::Vector2 oldCenter =
            raylib::Vector2 {static_cast<float>(_x), static_cast<float>(_y)} *
                Tile::TILE_SIZE -
            mapSize / 2.0f;
        raylib::Vector2 newCenter =
            raylib::Vector2 {static_cast<float>(x), static_cast<float>(y)} *
                Tile::TILE_SIZE -
            mapSize / 2.0f;
        raylib::Vector2 delta = newCenter - oldCenter;
        _startPos += raylib::Vector3 {delta.x, 0, delta.y};
        _targetPos += raylib::Vector3 {delta.x, 0, delta.y};
        _x = x;
        _y = y;
        _targetX = x;
        _targetY = y;
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

    void Player::died()
    {
        _incantate = false;
        _fork = false;
        _eject = true;
        _dead = true;
        _walking = false;
        _rotate = false;
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

    std::size_t Player::getTile(std::size_t width) const
    {
        return _y * width + _x;
    }

    Player2D::PlayerInfo Player::getPlayerInfo() const
    {
        return Player2D::PlayerInfo {
            _id, _team, _level, _x, _y, _status, _inventory};
    }

    const raylib::Color &Player::getColor() const
    {
        return this->_color;
    }

    void Player::setColor(raylib::Color color) const
    {
        _color = color;
    }

    void Player::draw3D() const
    {
        this->_model.GetMaterials()[Players::GEM_MAT].maps[0].color =
            this->_gemColor;
        this->_model.UpdateAnimation(
            this->getCurrentAnimation(), this->_frameTime * ANIMATIONS_FPS);
        auto [axis, angle] = this->getRotation().ToAxisAngle();
        this->_model.Draw(this->_position,
            axis,
            Maths::RadToDeg(angle),
            this->_scale,
            _color);
    }

    void Player::finishAction()
    {
        if (_walking) {
            _x = _targetX;
            _y = _targetY;
        }
        if (_rotate) {
            _dir = _targetDir;
        }
        _walking = false;
        _rotate = false;
    }

    void Player::moveAction(float dt)
    {
        _timer -= dt;
        if (_walking) {
            auto progress = Maths::easeInOutSine(this->_timer / WALKING_TIME);
            this->_position = this->_targetPos.Lerp(this->_startPos, progress);
        }
        if (this->_rotate) {
            auto progress = Maths::easeInOutSine(this->_timer / ROTATE_TIME);
            this->_rotation =
                this->_targetRotation.Slerp(this->_startRotation, progress);
        }
    }

    void Player::update(float dt)
    {
        updateAction(dt);
        this->_frameTime = getNextFrame(this->_currentAnimation.wrapMode,
            this->_frameTime + dt,
            this->getCurrentAnimation().keyframeCount,
            ANIMATIONS_FPS);
    }

    void Player::updateAction(float dt)
    {
        if (_timer <= 0) {
            finishAction();
        } else {
            moveAction(dt);
        }
    }

    void Player::setAnimation(PlayerAnimations::Animation animation)
    {
        this->_currentAnimation = animation;
        auto anim = std::ranges::find(this->_modelAnimation,
            std::string(this->_currentAnimation.name),
            [](auto &anim) { return anim.name; });
        if (anim == this->_modelAnimation.end())
            throw std::runtime_error(
                std::string {"Animation "} + animation.name + " doesn't exist");
        this->_currentAnimationIndex = anim - this->_modelAnimation.begin();
        this->_frameTime = 0;
    }

    const ModelAnimation &Player::getCurrentAnimation() const
    {
        return this->_modelAnimation[this->_currentAnimationIndex];
    }

    ModelAnimation &Player::getCurrentAnimation()
    {
        return this->_modelAnimation[this->_currentAnimationIndex];
    }
} // namespace Zappy
