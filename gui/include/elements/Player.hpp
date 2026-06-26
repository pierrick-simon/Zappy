/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Player
*/

#ifndef PLAYER_HPP
    #define PLAYER_HPP

    #include <Model.hpp>
    #include <array>
    #include <functional>
    #include <map>
    #include <string>
    #include "GUIException.hpp"
    #include "Info.hpp"
    #include "Maths.hpp"
    #include "NewPlayerEvent.hpp"
    #include "Player2D.hpp"
    #include "PlayerAnimations.hpp"
    #include "PlayerStatus.hpp"
    #include "graphics/IDrawable3D.hpp"
    #include "graphics/IUpdatable.hpp"
    #include "graphics/Transformable3D.hpp"

namespace Zappy {
    class Player : public Graphics::Transformable3D,
                   public Graphics::IDrawable3D,
                   public Graphics::IUpdatable {
    public:
        static inline const std::array<Quaternion, 4> DIRECTION_TO_QUATERNION =
            {raylib::Quaternion::FromEuler(0, Maths::DegToRad(180.0f), 0),
                raylib::Quaternion::FromEuler(0, Maths::DegToRad(270.0f), 0),
                raylib::Quaternion::FromEuler(0, Maths::DegToRad(0.0f), 0),
                raylib::Quaternion::FromEuler(0, Maths::DegToRad(90.0f), 0)};

        Player(const Shared::NewPlayerEvent::NewPlayer &player,
            std::ofstream &logFile, raylib::Model &model,
            std::vector<::ModelAnimation> &modelAnimation);
        static raylib::Vector3 getRandomOffset();

        void initPos(raylib::Vector2 pos);
        bool isMovementAcrossMap() const;
        void move(std::size_t _x, std::size_t _y, raylib::Vector2 target,
            Info::Direction _dir);
        void teleport(std::size_t x, std::size_t y, raylib::Vector2 newPos);

        void addLevel();
        void setLevel(std::size_t level);
        void setInventory(const std::vector<std::size_t> &inventory);
        void setIncantate(bool incantate);
        void setFork(bool fork);
        void setEject(bool eject);
        void died();
        void takeResource(Info::ResourceName resource);
        void setResource(Info::ResourceName resource);

        [[nodiscard]] std::size_t getTile(std::size_t width) const;

        [[nodiscard]] bool isDead() const
        {
            return _dead;
        }

        [[nodiscard]] std::string getTeam() const
        {
            return _team;
        }

        [[nodiscard]] std::size_t getLevel() const
        {
            return _level;
        }

        [[nodiscard]] std::size_t getX() const
        {
            return _x;
        }

        [[nodiscard]] std::size_t getY() const
        {
            return _y;
        }

        [[nodiscard]] bool getEject() const
        {
            return _eject;
        }

        [[nodiscard]] std::map<Info::ResourceName, std::size_t>
        getResources() const
        {
            return _inventory;
        }

        [[nodiscard]] Player2D::PlayerInfo getPlayerInfo() const;

        [[nodiscard]] const raylib::Color &getColor() const;
        void setColor(raylib::Color color) const;

        class PlayerException : public GUIException {
        public:
            PlayerException(const std::string &str) :
                GUIException(str) {};
        };

        class PlayerNotFoundException : public PlayerException {
        public:
            PlayerNotFoundException(std::size_t id) :
                PlayerException(
                    "Player[" + std::to_string(id) + "] Not Found.") {};
        };

        class DeadPlayerException : public PlayerException {
        public:
            DeadPlayerException(std::size_t id) :
                PlayerException(
                    "Event on dead Player[" + std::to_string(id) + "].") {};
        };

        void draw3D() const override;
        void destroy();
        [[nodiscard]] bool canDestroy() const;
        void finishActions();
        void updateAcrossMapAction(float dt);
        void updateActions(float dt);

        void update(float dt) override;
        void handleActions(float dt);

        void setAnimation(PlayerAnimations::Animation animation);

        [[nodiscard]] const ModelAnimation &getCurrentAnimation() const;
        ModelAnimation &getCurrentAnimation();
        float getAnimationDuration();

        void setGemColor(raylib::Color gemColor)
        {
            this->_gemColor = gemColor;
        }

    private:
        std::size_t _id;
        std::size_t _x;
        std::size_t _y;
        std::size_t _level;
        Info::Direction _dir;
        std::string _team;
        std::map<Info::ResourceName, std::size_t> _inventory;
        bool _incantate = false;
        bool _fork = false;
        bool _eject = false;
        bool _dead = false;
        bool _walking = false;
        bool _rotate = false;
        bool _acrossMap = false;

        raylib::Vector3 _startPos;
        raylib::Quaternion _startRotation;
        raylib::Quaternion _targetRotation;

        raylib::Vector3 _targetPos;
        std::size_t _targetX;
        std::size_t _targetY;
        Info::Direction _targetDir;

        float _timer = 0;

        PlayerStatus::Status _status;

        mutable raylib::Color _color;

        std::ofstream &_logFile;

        raylib::Model &_model;
        std::vector<::ModelAnimation> &_modelAnimation;
        float _frameTime {0.0f};
        raylib::Color _gemColor {251, 110, 0};
        PlayerAnimations::Animation _currentAnimation {PlayerAnimations::IDLE};
        size_t _currentAnimationIndex {0};
        float _animationSpeedScale {1.0f};
        bool _destroy {false};

        static constexpr auto ANIMATIONS_FPS = 30.0f;
        static constexpr float WALKING_TIME = 6.f;
        static constexpr float ROTATE_TIME = 6.f;

        static constexpr float ACROSS_MAP_DIG_TIME_PERCENT = 0.25f;
        static const std::map<float, std::function<void(Player &)>>
            ACROSS_MAP_ANIMATION_KEYFRAMES;

        static constexpr auto PLAYER_POSITION_PADDING = .75f;
    };
} // namespace Zappy

#endif
