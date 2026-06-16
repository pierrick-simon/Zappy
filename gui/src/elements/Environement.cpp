/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#include "Environement.hpp"
#include "GUICommunication.hpp"
#include "Utils.hpp"

namespace ClientCmd = Shared::GUICommunication::Client;
namespace ServerCmd = Shared::GUICommunication::Server;

namespace Zappy {
    Environement::Environement(int port, const std::string &ip,
        std::ofstream &logFile, bool &isConnect) :
        _connect(port, ip),
        _logFile(logFile),
        _isConnect(isConnect),
        _timeUnit(0)
    {
        _isConnect = false;
    }

    bool Environement::update()
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
            if (iter != EVENTS.end()) {
                iter->second(*this, stream);
                Shared::Utils::logMsg(_logFile,
                    "Recieved event " + iter->first + " from server.");
            } else {
                Shared::Utils::logMsg(
                    _logFile, "Event " + event + " not handle yet.");
            }
        }
    }

    void Environement::loading()
    {
        handleEvents();
        _loading = !_map.getHeight() || !_map.getWidth() || _teams.empty() ||
            !_timeUnit;
        _isConnect = !_loading;
    }

    Player &Environement::getPlayer(std::size_t id)
    {
        auto find = _players.find(id);
        if (find == _players.end())
            throw Player::PlayerNotFoundException(id);
        if (find->second.isDead())
            throw Player::DeadPlayerException(id);
        return find->second;
    }

    const std::unordered_map<std::string, Environement::Event>
        Environement::EVENTS = {
            {ServerCmd::MSZ.getStr(), &Environement::mapSize},
            {ServerCmd::BCT.getStr(), &Environement::updateTile},
            {ServerCmd::TNA.getStr(), &Environement::teamName},
            {ServerCmd::PNW.getStr(), &Environement::newPlayer},
            {ServerCmd::PPO.getStr(), &Environement::playerPosition},
            {ServerCmd::PLV.getStr(), &Environement::playerLevel},
            {ServerCmd::PIN.getStr(), &Environement::playerInventory},
            {ServerCmd::PEX.getStr(), &Environement::playerExpulsion},
            {ServerCmd::PBC.getStr(), &Environement::playerBroadcast},
            {ServerCmd::PIC.getStr(), &Environement::startIncantate},
            {ServerCmd::PIE.getStr(), &Environement::endIncantate},
            {ServerCmd::PFK.getStr(), &Environement::eggLaying},
            {ServerCmd::PDR.getStr(), &Environement::setResource},
            {ServerCmd::PGT.getStr(), &Environement::takeResource},
            {ServerCmd::PDI.getStr(), &Environement::deadEgg},
            {ServerCmd::ENW.getStr(), &Environement::eggLaid},
            {ServerCmd::EBO.getStr(), &Environement::eggHatched},
            {ServerCmd::EDI.getStr(), &Environement::deadEgg},
            {ServerCmd::SGT.getStr(), &Environement::timeUnitRequest},
            {ServerCmd::SST.getStr(), &Environement::timeUnitModification},
            {ServerCmd::SEG.getStr(), &Environement::endOfGame},
            {ServerCmd::SMG.getStr(), &Environement::serverMsg},
            {ServerCmd::SUC.getStr(), &Environement::unknowCommand},
            {ServerCmd::SBP.getStr(), &Environement::badCommandParameter},
    };
} // namespace Zappy
