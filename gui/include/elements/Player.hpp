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
    #include <string>
    #include "GUIException.hpp"
    #include "Info.hpp"
    #include "Maths.hpp"
    #include "NewPlayerEvent.hpp"
    #include "Player2D.hpp"
    #include "PlayerStatus.hpp"
    #include "graphics/IDrawable3D.hpp"
    #include "graphics/Transformable3D.hpp"

namespace Zappy {
    class Player : public Graphics::Transformable3D,
                   public Graphics::IDrawable3D {
    public:
        Player(const Shared::NewPlayerEvent::NewPlayer &player,
            std::ofstream &logFile, raylib::Model &model);

        void move(std::size_t _x, std::size_t _y, Info::Direction _dir);

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

        [[nodiscard]] std::map<Info::ResourceName, std::size_t>
        getResources() const
        {
            return _inventory;
        }

        [[nodiscard]] Player2D::PlayerInfo getPlayerInfo() const;

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

        PlayerStatus::Status _status;

        std::ofstream &_logFile;
        raylib::Model &_model;

        static inline const std::array<Quaternion, 4> DIRECTION_TO_QUATERNION =
            {raylib::Quaternion::FromEuler(0, Maths::DegToRad(0.0f), 0),
                raylib::Quaternion::FromEuler(0, Maths::DegToRad(90.0f), 0),
                raylib::Quaternion::FromEuler(0, Maths::DegToRad(180.0f), 0),
                raylib::Quaternion::FromEuler(0, Maths::DegToRad(270.0f), 0)};
    };
} // namespace Zappy

#endif
