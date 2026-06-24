/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Events
*/

#include <algorithm>
#include <iostream>

#include "Environement.hpp"
#include "GUICommunication.hpp"
#include "GUIEvents.hpp"
#include "Info.hpp"
#include "Utils.hpp"

namespace ClientCmd = Shared::GUICommunication::Client;

namespace Zappy {
    void Environement::mapSize(std::istringstream stream)
    {
        Shared::MapSizeEvent event;
        event.retrieve(std::move(stream));
        if (_map.updateSize(event.getX(), event.getY()))
            Shared::Connect::send(
                _connect.getFd(), ClientCmd::MCT.getStr() + "\n");
    }

    void Environement::updateTile(std::istringstream stream)
    {
        Shared::TileInfoEvent event;
        event.retrieve(std::move(stream));
        _map.updateTile(event.getX(), event.getY(), event.getResources());
    }

    void Environement::teamName(std::istringstream stream)
    {
        Shared::TeamNameEvent event;
        event.retrieve(std::move(stream));
        if (_teams.contains(event.getTeam()))
            return;
        _teams.emplace(event.getTeam(), _colorGenerator.next());
    }

    void Environement::newPlayer(std::istringstream stream)
    {
        Shared::NewPlayerEvent event;
        event.retrieve(std::move(stream));
        auto player = event.getPlayer();
        auto value = _players.addPlayer(player);
        if (value) {
            _overlay.eventBox.addMessage(
                player.team, player.id, "Joined the game.");
            Shared::Connect::send(_connect.getFd(),
                ClientCmd::PIN.getStr() + " #" + std::to_string(player.id) +
                    "\n" + ClientCmd::PLV.getStr() + " #" +
                    std::to_string(player.id) + "\n");
            auto mapPos = this->_map.getTilePosition(player.x, player.y);
            (*value).get().setPosition({mapPos.x, 0, mapPos.y});
            (*value).get().setRotation(
                Player::DIRECTION_TO_QUATERNION[static_cast<std::size_t>(
                    Info::getDirection(player.dir))]);
        }
    }

    void Environement::playerPosition(std::istringstream stream)
    {
        Shared::PlayerPositionEvent event;
        event.retrieve(std::move(stream));
        try {
            auto &player = _players.getPlayer(event.getId());
            std::size_t x = event.getX() % _width;
            std::size_t y = event.getY() % _height;
            if (player.getEject()) {
                player.teleport(x, y, _width, _height);
                _overlay.eventBox.addMessage(player.getTeam(),
                    event.getId(),
                    "Ejected to (" + std::to_string(x) + "," +
                        std::to_string(y) + ").");
            } else {
                auto dir = Info::getDirection(event.getDir());
                auto mapPos = this->_map.getTilePosition(x, y);
                player.move(x, y, mapPos, dir);
                _overlay.eventBox.addMessage(player.getTeam(),
                    event.getId(),
                    "Moving to (" + std::to_string(x) + "," +
                        std::to_string(y) + ").");
            }
        } catch (Info::DirectionNotFoundException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::playerLevel(std::istringstream stream)
    {
        Shared::PlayerLevelEvent event;
        event.retrieve(std::move(stream));
        try {
            auto &player = _players.getPlayer(event.getId());
            player.setLevel(event.getLevel());
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::playerInventory(std::istringstream stream)
    {
        Shared::PlayerInventoryEvent event;
        event.retrieve(std::move(stream));
        try {
            auto &player = _players.getPlayer(event.getId());
            auto before = player.getResources();
            player.setInventory(event.getResources());
            auto after = player.getResources();
            _players.updateTotalResources(before, after);
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::playerExpulsion(std::istringstream stream)
    {
        Shared::PlayerExpulsionEvent event;
        event.retrieve(std::move(stream));
        try {
            auto &player = _players.getPlayer(event.getId());
            player.setEject(true);
            _overlay.eventBox.addMessage(
                player.getTeam(), event.getId(), "Been push.");
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::playerBroadcast(std::istringstream stream)
    {
        Shared::BroadcastEvent event;
        event.retrieve(std::move(stream));
        try {
            auto &player = _players.getPlayer(event.getId());
            _overlay.chatBox.addMessage(
                player.getTeam(), event.getId(), event.getText());
            _overlay.eventBox.addMessage(
                player.getTeam(), event.getId(), "Started talking.");
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::startIncantate(std::istringstream stream)
    {
        Shared::StartIncantationEvent event;
        event.retrieve(std::move(stream));
        auto list = event.getIds();
        std::vector<std::size_t> players;
        for (auto id : list) {
            try {
                auto &player = _players.getPlayer(id);
                players.push_back(id);
                player.setIncantate(true);
                _overlay.eventBox.addMessage(
                    player.getTeam(), id, "Started incantade.");
            } catch (Player::PlayerException &e) {
                Shared::Utils::logMsg(_logFile, e.what());
            }
        }
        _elevations.addElevation(event.getX(),
            event.getY(),
            event.getLevel(),
            players,
            _map.getTilePosition(event.getX(), event.getY()));
    }

    void Environement::playersEndIncantate(
        std::vector<std::size_t> &players, bool success)
    {
        for (auto id : players) {
            try {
                auto &player = _players.getPlayer(id);
                player.setIncantate(false);
                _overlay.eventBox.addMessage(player.getTeam(),
                    id,
                    success ? "Succeeded to incantate."
                            : "Failed to incantate.");
                if (success)
                    player.addLevel();
            } catch (Player::PlayerException &e) {
                Shared::Utils::logMsg(_logFile, e.what());
            }
        }
    }

    void Environement::endIncantate(std::istringstream stream)
    {
        Shared::EndIncantationEvent event;
        event.retrieve(std::move(stream));
        auto players = _elevations.endElevation(event.getX(), event.getY());
        playersEndIncantate(players, event.getResult());
    }

    void Environement::eggLaying(std::istringstream stream)
    {
        Shared::EggLayingEvent event;
        event.retrieve(std::move(stream));
        try {
            auto &player = _players.getPlayer(event.getId());
            player.setFork(true);
            _overlay.eventBox.addMessage(
                player.getTeam(), event.getId(), "Laying an egg.");
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::takeResource(std::istringstream stream)
    {
        Shared::TakeResourceEvent event;
        event.retrieve(std::move(stream));
        try {
            auto &player = _players.getPlayer(event.getId());
            auto resource = Info::getResource(event.getNb());
            auto before = player.getResources();
            player.takeResource(resource);
            auto after = player.getResources();
            _players.updateTotalResources(before, after);
            _overlay.eventBox.addMessage(player.getTeam(),
                event.getId(),
                "Take " + Info::getResourceName(resource) + ".");
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        } catch (Info::ResourceNotFoundException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::setResource(std::istringstream stream)
    {
        Shared::SetResourceEvent event;
        event.retrieve(std::move(stream));
        try {
            auto &player = _players.getPlayer(event.getId());
            auto resource = Info::getResource(event.getNb());
            auto before = player.getResources();
            player.setResource(resource);
            auto after = player.getResources();
            _players.updateTotalResources(before, after);
            _overlay.eventBox.addMessage(player.getTeam(),
                event.getId(),
                "Set " + Info::getResourceName(resource) + ".");
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        } catch (Info::ResourceNotFoundException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::deadPlayer(std::istringstream stream)
    {
        Shared::PlayerDeathEvent event;
        event.retrieve(std::move(stream));
        try {
            auto &player = _players.getPlayer(event.getId());
            auto before = player.getResources();
            player.died();
            _elevations.removePlayer(event.getId());
            _players.updateTotalResources(before, {});
            _overlay.eventBox.addMessage(
                player.getTeam(), event.getId(), "Died.");
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::eggLaid(std::istringstream stream)
    {
        Shared::EggLaidEvent event;
        event.retrieve(std::move(stream));
        try {
            auto &player = _players.getPlayer(event.getPlayerId());
            player.setFork(false);
            _eggs.emplace(event.getEggId(),
                Egg {event.getX(), event.getY(), player.getTeam()});
            _overlay.eventBox.addMessage(
                player.getTeam(), event.getPlayerId(), "Laid an egg.");
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::eggHatched(std::istringstream stream)
    {
        Shared::EggHatchedEvent event;
        event.retrieve(std::move(stream));
        auto find = _eggs.find(event.getId());
        if (find != _eggs.end())
            _eggs.erase(find);
    }

    void Environement::deadEgg(std::istringstream stream)
    {
        Shared::EggDestroyEvent event;
        event.retrieve(std::move(stream));
        auto find = _eggs.find(event.getId());
        if (find != _eggs.end())
            _eggs.erase(find);
    }

    void Environement::timeUnitRequest(std::istringstream stream)
    {
        Shared::GetTimeUnit event;
        event.retrieve(std::move(stream));
        _timeUnit = event.getNb();
    }

    void Environement::timeUnitModification(std::istringstream stream)
    {
        Shared::SetTimeUnit event;
        event.retrieve(std::move(stream));
        _timeUnit = event.getNb();
    }

    void Environement::endOfGame(std::istringstream stream)
    {
        Shared::EndOfGameEvent event;
        event.retrieve(std::move(stream));
        _winingTeam = event.getStr();
        _end = true;
        Shared::Utils::logMsg(_logFile,
            "End of game: the " + _winingTeam + " team won the game.");
    }

    void Environement::serverMsg(std::istringstream stream)
    {
        Shared::ServerMsgEvent event;
        event.retrieve(std::move(stream));
        Shared::Utils::logMsg(
            _logFile, "Server Message: " + event.getStr() + ".");
    }

    void Environement::unknowCommand(std::istringstream stream)
    {
        Shared::Utils::logMsg(
            _logFile, "Send an Unknow command to the server.");
    }

    void Environement::badCommandParameter(std::istringstream stream)
    {
        Shared::Utils::logMsg(
            _logFile, "Send a command with bad parameters to the server.");
    }

    void Environement::eggEvent(std::istringstream stream)
    {
        Shared::EggEvent event;
        event.retrieve(std::move(stream));
        _eggs.emplace(
            event.getId(), Egg {event.getX(), event.getY(), event.getTeam()});
    }
} // namespace Zappy
