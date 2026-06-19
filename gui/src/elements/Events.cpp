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
    void Environement::mapSize(std::istringstream &stream)
    {
        Shared::MapSizeEvent event;
        event.retrieve(stream);
        if (_map.updateSize(event.getX(), event.getY()))
            Shared::Connect::send(
                _connect.getFd(), ClientCmd::MCT.getStr() + "\n");
    }

    void Environement::updateTile(std::istringstream &stream)
    {
        Shared::TileInfoEvent event;
        event.retrieve(stream);
        _map.updateTile(event.getX(), event.getY(), event.getResources());
    }

    void Environement::teamName(std::istringstream &stream)
    {
        Shared::TeamNameEvent event;
        event.retrieve(stream);
        for (const auto &team : _teams) {
            if (team == event.getTeam())
                return;
        }
        _teams.push_back(event.getTeam());
    }

    void Environement::newPlayer(std::istringstream &stream)
    {
        Shared::NewPlayerEvent event;
        event.retrieve(stream);
        auto player = event.getPlayer();
        if (_players.addPlayer(player))
            Shared::Connect::send(_connect.getFd(),
                ClientCmd::PIN.getStr() + "\n" + ClientCmd::PLV.getStr() +
                    "\n");
    }

    void Environement::playerPosition(std::istringstream &stream)
    {
        Shared::PlayerPositionEvent event;
        event.retrieve(stream);
        try {
            auto player = _players.getPlayer(event.getId());
            auto dir = Info::getDirection(event.getDir());
            player.move(event.getX(), event.getY(), dir);
        } catch (Info::DirectionNotFoundException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::playerLevel(std::istringstream &stream)
    {
        Shared::PlayerLevelEvent event;
        event.retrieve(stream);
        try {
            auto player = _players.getPlayer(event.getId());
            player.setLevel(event.getLevel());
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::playerInventory(std::istringstream &stream)
    {
        Shared::PlayerInventoryEvent event;
        event.retrieve(stream);
        try {
            auto player = _players.getPlayer(event.getId());
            auto before = player.getResources();
            player.setInventory(event.getResources());
            auto after = player.getResources();
            _players.updateTotalResources(before, after);
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::playerExpulsion(std::istringstream &stream)
    {
        Shared::PlayerExpulsionEvent event;
        event.retrieve(stream);
        try {
            auto player = _players.getPlayer(event.getId());
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::playerBroadcast(std::istringstream &stream)
    {
        Shared::BroadcastEvent event;
        event.retrieve(stream);
        try {
            auto player = _players.getPlayer(event.getId());
            _msg.push(Message {event.getId(), event.getText()});
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::startIncantate(std::istringstream &stream)
    {
        Shared::StartIncantationEvent event;
        event.retrieve(stream);
        auto list = event.getIds();
        std::map<std::size_t, bool> players;
        for (auto id : list) {
            try {
                auto player = _players.getPlayer(id);
                players.emplace(id, false);
                player.setIncantate(true);
            } catch (Player::PlayerException &e) {
                Shared::Utils::logMsg(_logFile, e.what());
                players.emplace(id, true);
            }
        }
        _elevations.emplace_back(
            event.getX(), event.getY(), event.getLevel(), players);
    }

    void Environement::playersEndIncantate(std::map<std::size_t, bool> &players)
    {
        for (auto &[id, dead] : players) {
            if (dead)
                continue;
            try {
                auto player = _players.getPlayer(id);
                player.setIncantate(false);
            } catch (Player::PlayerException &e) {
                dead = true;
                Shared::Utils::logMsg(_logFile, e.what());
            }
        }
    }

    void Environement::endIncantate(std::istringstream &stream)
    {
        Shared::EndIncantationEvent event;
        event.retrieve(stream);
        for (auto elevation : _elevations) {
            if (!elevation.getFinish() && elevation.getX() == event.getX() &&
                elevation.getY() == event.getY()) {
                elevation.setFinish(true);
                playersEndIncantate(elevation.getPlayers());
                return;
            }
        }
        Shared::Utils::logMsg(_logFile,
            "Incantation in (" + std::to_string(event.getX()) + "," +
                std::to_string(event.getY()) + ") Not Found.");
    }

    void Environement::eggLaying(std::istringstream &stream)
    {
        Shared::EggLayingEvent event;
        event.retrieve(stream);
        try {
            auto player = _players.getPlayer(event.getId());
            player.setFork(true);
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::takeResource(std::istringstream &stream)
    {
        Shared::TakeResourceEvent event;
        event.retrieve(stream);
        try {
            auto player = _players.getPlayer(event.getId());
            auto resource = Info::getResource(event.getNb());
            auto before = player.getResources();
            player.takeResource(resource);
            auto after = player.getResources();
            _players.updateTotalResources(before, after);
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        } catch (Info::ResourceNotFoundException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::setResource(std::istringstream &stream)
    {
        Shared::SetResourceEvent event;
        event.retrieve(stream);
        try {
            auto player = _players.getPlayer(event.getId());
            auto resource = Info::getResource(event.getNb());
            auto before = player.getResources();
            player.setResource(resource);
            auto after = player.getResources();
            _players.updateTotalResources(before, after);
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        } catch (Info::ResourceNotFoundException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::incantateDeadPlayer(std::size_t id)
    {
        for (auto elevation : _elevations) {
            auto players = elevation.getPlayers();
            auto find = std::find_if(players.begin(),
                players.end(),
                [id](const std::pair<const unsigned long, bool> &p) {
                    return p.first == id;
                });
            if (find != players.end())
                find->second = true;
        }
    }

    void Environement::deadPlayer(std::istringstream &stream)
    {
        Shared::PlayerDeathEvent event;
        event.retrieve(stream);
        try {
            auto player = _players.getPlayer(event.getId());
            auto before = player.getResources();
            player.died();
            incantateDeadPlayer(event.getId());
            _players.updateTotalResources(before, Info::INIT_RESOUCES);
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::eggLaid(std::istringstream &stream)
    {
        Shared::EggLaidEvent event;
        event.retrieve(stream);
        try {
            auto player = _players.getPlayer(event.getPlayerId());
            player.setFork(false);
            _eggs.emplace(event.getEggId(),
                Egg {event.getX(), event.getY(), player.getTeam()});
        } catch (Player::PlayerException &e) {
            Shared::Utils::logMsg(_logFile, e.what());
        }
    }

    void Environement::eggHatched(std::istringstream &stream)
    {
        Shared::EggHatchedEvent event;
        event.retrieve(stream);
        auto find = _eggs.find(event.getId());
        if (find != _eggs.end())
            _eggs.erase(find);
    }

    void Environement::deadEgg(std::istringstream &stream)
    {
        Shared::EggDestroyEvent event;
        event.retrieve(stream);
        auto find = _eggs.find(event.getId());
        if (find != _eggs.end())
            _eggs.erase(find);
    }

    void Environement::timeUnitRequest(std::istringstream &stream)
    {
        Shared::GetTimeUnit event;
        event.retrieve(stream);
        _timeUnit = event.getNb();
    }

    void Environement::timeUnitModification(std::istringstream &stream)
    {
        Shared::SetTimeUnit event;
        event.retrieve(stream);
        _timeUnit = event.getNb();
    }

    void Environement::endOfGame(std::istringstream &stream)
    {
        Shared::EndOfGameEvent event;
        event.retrieve(stream);
        _winingTeam = event.getStr();
        _end = true;
        Shared::Utils::logMsg(_logFile,
            "End of game: the " + _winingTeam + " team won the game.");
    }

    void Environement::serverMsg(std::istringstream &stream)
    {
        Shared::ServerMsgEvent event;
        event.retrieve(stream);
        Shared::Utils::logMsg(
            _logFile, "Server Message: " + event.getStr() + ".");
    }

    void Environement::unknowCommand(std::istringstream &stream)
    {
        Shared::Utils::logMsg(
            _logFile, "Send an Unknow command to the server.");
    }

    void Environement::badCommandParameter(std::istringstream &stream)
    {
        Shared::Utils::logMsg(
            _logFile, "Send a command with bad parameters to the server.");
    }
} // namespace Zappy
