/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#include "Environement.hpp"
#include <chrono>
#include <iostream>
#include <thread>
#include "GUICommunication.hpp"
#include "Utils.hpp"
#include "UtilsVector.hpp"
#include "graphics/primitives/Text2D.hpp"

#include "Resources.hpp"

namespace ClientCmd = Shared::GUICommunication::Client;
namespace ServerCmd = Shared::GUICommunication::Server;

namespace Zappy {
    Environement::Environement(int port, const std::string &ip,
        std::ofstream &logFile, bool &isConnect) :
        _map(_width, _height, _selectPlayer, _selectTile),
        _players(logFile, _timeUnit, _selectPlayer, _selectTile),
        _timeUnit(0),
        _connect(port, ip),
        _isConnect(isConnect),
        _logFile(logFile),
        _overlay(_teams),
        _elevations(_selectPlayer, _selectTile, _width, _timeUnit)
    {
        _isConnect = false;
    }

    bool Environement::updateFromServer()
    {
        bool connected = true;
        auto info = _connect.infoToRead(0);
        if (!info.empty() && !infoToRead())
            connected = false;
        else {
            if (!_loading && !_isConnect)
                connected = connect();
            else if (!_isConnect)
                loading();
            else
                handleEvents();
        }
        return connected;
    }

    void Environement::update(float dt)
    {
        auto deltaTimeUnit = dt * float(_timeUnit);
        _overlay.resources.update(
            _map.getTotalResources(), _players.getTotalResources());
        _elevations.update(dt);
        if (_selectPlayer)
            updatePlayerInfo();
        else if (_selectTile)
            updateTileInfo();
        else
            updateTeamInfo();
        updateTimeUnit();
        this->_players.update(dt);
        _map.update(dt);
    }

    void Environement::setShader(Graphics::Shader &shader)
    {
        AShadered::setShader(shader);
        this->_map.setShader(shader);
        this->_players.setShader(shader);
        this->_eggModel.materials[1].shader = this->getShader().asShader();
    }

    void Environement::draw3D() const
    {
        this->_map.draw3D();
        this->_players.draw3D();
        this->_elevations.draw3D();
        for (const auto &[_, egg] : this->_eggs)
            egg.draw3D();
    }

    void Environement::draw2D() const
    {
        _overlay.resources.draw2D();
        _overlay.chatBox.draw2D();
        _overlay.eventBox.draw2D();
        _elevations.draw2D();
        _overlay.timeUnit.draw2D();
        if (_selectPlayer)
            _overlay.player.draw2D();
        else if (_selectTile)
            _overlay.tile.draw2D();
        else
            _overlay.team.draw2D();
    }

    void Environement::event(raylib::Camera3D &camera,
        const raylib::Vector2 &mouse, const Ray &ray, bool &leftClick)
    {
        if (_selectPlayer)
            _overlay.player.event(camera, mouse, ray, leftClick);
        else if (_selectTile)
            _overlay.tile.event(camera, mouse, ray, leftClick);
        else
            _overlay.team.event(camera, mouse, ray, leftClick);
        _elevations.event(camera, mouse, ray, leftClick);
        _overlay.timeUnit.event(camera, mouse, ray, leftClick);
        _players.event(camera, mouse, ray, leftClick);
        _map.event(camera, mouse, ray, leftClick);
        if (raylib::Keyboard::IsKeyPressed(KEY_ONE)) {
            _selectTile = std::nullopt;
            _selectPlayer = std::nullopt;
        }
        if (raylib::Keyboard::IsKeyPressed(KEY_TWO) &&
            _players.getNbPlayer() > 0) {
            _selectTile = std::nullopt;
            _selectPlayer = _players.getFirstPlayerId();
        }
        if (raylib::Keyboard::IsKeyPressed(KEY_THREE) && _width * _height > 0) {
            _selectTile = 0;
            _selectPlayer = std::nullopt;
        }
    }

    bool Environement::connect()
    {
        bool value = true;

        if (!_events.empty()) {
            if (_events.front() == WELCOME) {
                _events.pop();
                Shared::Connect::send(
                    _connect.getFd(), std::string(TEAM) + "\n");
                _loading = true;
                Shared::Utils::logMsg(
                    _logFile, "Client GUI connect to the server.");
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(SMALL_SLEEP));
                Shared::Connect::send(
                    _connect.getFd(), ClientCmd::MSZ.getStr() + "\n");
                Shared::Connect::send(
                    _connect.getFd(), ClientCmd::TNA.getStr() + "\n");
                Shared::Connect::send(
                    _connect.getFd(), ClientCmd::SGT.getStr() + "\n");
            } else {
                value = false;
                Shared::Utils::logMsg(
                    _logFile, "Client GUI Close (Wrong Connection Message).");
            }
        }
        return value;
    }

    bool Environement::infoToRead()
    {
        try {
            Shared::Connect::receiveChunk(_connect.getFd(), _buffer);
        } catch (Shared::Connect::CloseException &_) {
            Shared::Utils::logMsg(
                _logFile, "Client GUI Close (Server Disconnected).");
            return false;
        }
        auto line = Shared::Utils::parseLine(_buffer);
        while (line) {
            if (!line->empty())
                _events.push(*line);
            line = Shared::Utils::parseLine(_buffer);
        }
        return true;
    }

    void Environement::handleEvents()
    {
        while (!_events.empty()) {
            std::istringstream stream(_events.front());
            std::string event;
            stream >> event;
            _events.pop();
            if (stream.fail())
                return;
            auto iter = EVENTS.find(event);
            if (iter != EVENTS.end() &&
                (!_loading || iter->second.loadingInfo)) {
                Shared::Utils::logMsg(_logFile,
                    "Recieved event " + iter->first + " from server.");
                iter->second.func(*this, std::move(stream));
            } else {
                Shared::Utils::logMsg(
                    _logFile, "Event " + event + " not handle yet.");
            }
        }
    }

    void Environement::updatePlayerInfo()
    {
        try {
            auto player = _players.getPlayer(*_selectPlayer);
            auto value = _overlay.player.update(player.getPlayerInfo());
            if (value == InfoBox::Action::CLOSE) {
                _selectPlayer = std::nullopt;
                updateTeamInfo();
            } else
                _selectPlayer = _players.getNextPlayer(value, *_selectPlayer);
        } catch (Player::PlayerException &_) {
            _selectPlayer = std::nullopt;
            updateTeamInfo();
        }
    }

    void Environement::updateTileInfo()
    {
        if (*_selectTile >= _width * _height) {
            _selectTile = std::nullopt;
            return updateTeamInfo();
        }
        auto nbPlayer = _players.getNbTilePlayers(*_selectTile, _width);
        std::size_t nbEgg = 0;
        for (const auto &[_, egg] : _eggs) {
            if (egg.getTile(_width) == *_selectTile)
                nbEgg++;
        }
        auto nbElevation =
            _elevations.getNbTileElevations(*_selectTile, _width);
        auto resources = _map.getTileResources(*_selectTile);
        auto value = _overlay.tile.update({*_selectTile % _width,
            *_selectTile / _width,
            nbPlayer,
            nbEgg,
            nbElevation,
            resources});
        if (value == InfoBox::Action::CLOSE) {
            _selectTile = std::nullopt;
            updateTeamInfo();
        } else
            _selectTile = _map.getNextTile(value, *_selectTile);
    }

    void Environement::updateTeamInfo()
    {
        auto team = _overlay.team.getSelectTeam();
        if (!team) {
            if (_teams.empty())
                return;
            team = _teams.begin()->first;
            _overlay.team.setSelectTeam(*team);
        }
        std::size_t nbEgg = 0;
        for (const auto &[_, egg] : _eggs) {
            if (egg.getTeam() == *team)
                nbEgg++;
        }
        _overlay.team.update({nbEgg, _players.getTeamPlayers(*team)});
    }

    void Environement::loading()
    {
        handleEvents();
        _loading = !_map.getHeight() || !_map.getWidth() || _teams.empty() ||
            !_timeUnit;
        _isConnect = !_loading;
    }

    void Environement::updateTimeUnit()
    {
        if (_timeUnit == 0)
            return;
        auto tmp = _overlay.timeUnit.update(_timeUnit);
        if (tmp != _timeUnit)
            Shared::Connect::send(_connect.getFd(),
                ClientCmd::SST.getStr() + " " + std::to_string(tmp) + "\n");
    }

    const std::unordered_map<std::string, Environement::Event>
        Environement::EVENTS = {
            {ServerCmd::MSZ.getStr(), {&Environement::mapSize, true}},
            {ServerCmd::BCT.getStr(), {&Environement::updateTile, true}},
            {ServerCmd::TNA.getStr(), {&Environement::teamName, true}},
            {ServerCmd::PNW.getStr(), {&Environement::newPlayer, true}},
            {ServerCmd::PPO.getStr(), {&Environement::playerPosition, false}},
            {ServerCmd::PLV.getStr(), {&Environement::playerLevel, false}},
            {ServerCmd::PIN.getStr(), {&Environement::playerInventory, false}},
            {ServerCmd::PEX.getStr(), {&Environement::playerExpulsion, false}},
            {ServerCmd::PBC.getStr(), {&Environement::playerBroadcast, false}},
            {ServerCmd::PIC.getStr(), {&Environement::startIncantate, false}},
            {ServerCmd::PIE.getStr(), {&Environement::endIncantate, false}},
            {ServerCmd::PFK.getStr(), {&Environement::eggLaying, false}},
            {ServerCmd::PDR.getStr(), {&Environement::setResource, false}},
            {ServerCmd::PGT.getStr(), {&Environement::takeResource, false}},
            {ServerCmd::PDI.getStr(), {&Environement::deadPlayer, false}},
            {ServerCmd::ENW.getStr(), {&Environement::eggLaid, false}},
            {ServerCmd::EBO.getStr(), {&Environement::eggHatched, false}},
            {ServerCmd::EDI.getStr(), {&Environement::deadEgg, false}},
            {ServerCmd::SGT.getStr(), {&Environement::timeUnitRequest, true}},
            {ServerCmd::SST.getStr(),
                {&Environement::timeUnitModification, true}},
            {ServerCmd::SEG.getStr(), {&Environement::endOfGame, false}},
            {ServerCmd::SMG.getStr(), {&Environement::serverMsg, false}},
            {ServerCmd::SUC.getStr(), {&Environement::unknowCommand, false}},
            {ServerCmd::SBP.getStr(),
                {&Environement::badCommandParameter, false}},
            {ServerCmd::EGG.getStr(), {&Environement::eggEvent, true}},
    };
} // namespace Zappy
