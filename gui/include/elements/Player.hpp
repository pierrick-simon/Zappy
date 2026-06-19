/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Player
*/

#ifndef PLAYER_HPP
    #define PLAYER_HPP

    #include <fstream>
    #include <string>
    #include "GUIException.hpp"
    #include "Info.hpp"
    #include "NewPlayerEvent.hpp"

namespace Zappy {
    class Player {
    public:
        Player(
            Shared::NewPlayerEvent::NewPlayer player, std::ofstream &logFile);
        ~Player();

        void move(std::size_t _x, std::size_t _y, Info::Direction _dir);

        void setLevel(std::size_t level);
        void setInventory(const std::vector<std::size_t> &inventory);
        void setIncantate(bool incantate);
        void setFork(bool fork);
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

        [[nodiscard]] std::map<Info::ResourceName, std::size_t>
        getResources() const
        {
            return _inventory;
        }

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
        bool _dead = false;

        std::ofstream &_logFile;
    };
} // namespace Zappy

#endif
