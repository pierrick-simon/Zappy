/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Server
*/

#include "Server.hpp"
#include <csignal>
#include <iostream>
#include "ArgsParser.hpp"
#include "Utils.hpp"

namespace Zappy {

    bool Server::RECEIVED_SIG_INT = false;

    Server::Server(std::vector<std::string> args) :
        _logFile(std::string(LOG_FILE)),
        _teamsNames(Parser::ArgsParser::getArgList<std::string>(
            args, "-n", DEFAULT_TEAMS)),
        _connect(Parser::ArgsParser::getArg<int>(args, "-p", DEFAULT_PORT)),
        _f(Parser::ArgsParser::getArgSize(args, "-f", DEFAULT_FREQ)),
        _fn(std::chrono::nanoseconds(SECOND_IN_NANO / _f)),
        _env(Parser::ArgsParser::getArgSize(args, "-x", DEFAULT_X),
            Parser::ArgsParser::getArgSize(args, "-y", DEFAULT_Y), _logFile, _clients,
            _teams)
    {
        auto nbPerTeam = Parser::ArgsParser::getArgSize(args, "-c", 10);
        if (_teamsNames.empty())
            throw Parser::ArgsParserError("No teams name given");
        for (const auto &team : _teamsNames) {
            if (_teams.count(team))
                throw Parser::ArgsParserError(
                    "Cannot use duplicate teams name");
            if (team == GRAPHIC)
                throw Parser::ArgsParserError(
                    "Cannot use \"GRAPHIC\" as team name");
            _teams.emplace(team, nbPerTeam);
            for (std::size_t i = 0; i < nbPerTeam; i++)
                _env.spawnEgg(team);
        }
        _teamsNames.clear();

        if (!args.empty())
            throw Parser::Help();

        Shared::Utils::logMsg(_logFile, "Server Open.");
        signal(SIGINT, [](int) { RECEIVED_SIG_INT = true; });
        _clock = std::chrono::steady_clock::now();
    }

    Server::~Server()
    {
        Shared::Utils::logMsg(_logFile, "Server Close.");
    }

    void Server::run()
    {
        auto end = false;
        while (!RECEIVED_SIG_INT && !end) {
            infoToRead();
            end = update();
        }
    }

    void Server::infoToRead()
    {
        auto infos = _connect.infoToRead(_timeout);
        if (!infos.empty()) {
            if (infos[0] == _connect.getFd())
                addClient();
            handleClient(infos);
        }
    }

    bool Server::update()
    {
        auto now = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::nanoseconds((_clock - now) / _fn);
        _clock = now;
        _timeout = -1;
        updateEnv(elapsed);
        updateAi(elapsed);
        updateGui();
        return _env.getEnd();
    }

    void Server::updateEnv(std::chrono::nanoseconds elapsed)
    {
        auto tmp = _env.update(elapsed);
        auto timeout = int(
            std::chrono::duration_cast<std::chrono::microseconds>(tmp).count());
        if (tmp.count() > 0 && (_timeout = -1 || timeout < _timeout))
            _timeout = timeout;
    }

    void Server::updateAi(std::chrono::nanoseconds elapsed)
    {
        std::vector<int> deads;
        for (auto &[id, ai] : _clients.ai) {
            auto tmp = ai.update(elapsed);
            auto timeout =
                int(std::chrono::duration_cast<std::chrono::microseconds>(tmp)
                        .count());
            if (tmp.count() > 0 && (_timeout = -1 || timeout < _timeout))
                _timeout = timeout;
            if (!ai.isAlive())
                deads.push_back(id);
        }
        handleDeadClient(deads);
    }

    void Server::updateGui()
    {
        for (auto &[_, gui] : _clients.gui) {
            auto tmp = gui.timeUnitUpdate();
            if (tmp && *tmp != _f) {
                _f = *tmp;
                _fn = std::chrono::nanoseconds(SECOND_IN_NANO / _f);
                gui.timeUnitEvent(_f);
            }
        }
    }

    void Server::handleDeadClient(const std::vector<int> &deads)
    {
        for (auto dead : deads) {
            auto find = _clients.ai.find(dead);
            if (find != _clients.ai.end()) {
                _connect.removeClient(dead);
                _env.removePlayer(find);
                _clients.ai.erase(find);
            }
        }
    }

    void Server::addClient()
    {
        static std::size_t id = 0;
        auto new_fd = _connect.acceptClient();
        _connect.addClient(new_fd);
        Shared::Connect::send(new_fd, "WELCOME\n");
        _clients.newClient.emplace(new_fd, std::make_pair(id, std::string()));
        Shared::Utils::logMsg(
            _logFile, "New client[" + std::to_string(id) + "].");
        id++;
    }

    void Server::handleClient(const std::vector<int> &infos)
    {
        for (const auto fd : infos) {
            auto ai = _clients.ai.find(fd);
            if (ai != _clients.ai.end()) {
                handleAIClient(ai);
                continue;
            }
            auto gui = _clients.gui.find(fd);
            if (gui != _clients.gui.end()) {
                handleGUIClient(gui);
                continue;
            }
            auto newClient = _clients.newClient.find(fd);
            if (newClient != _clients.newClient.end())
                handleNewClient(newClient);
        }
    }

    void Server::handleAIClient(AIIter iter)
    {
        try {
            iter->second.infoToRead();
        } catch (Shared::Connect::CloseException &_) {
            _connect.removeClient(iter->first);
            _env.removePlayer(iter);
            _clients.ai.erase(iter);
            Shared::Utils::logMsg(_logFile,
                "Client[" + std::to_string(iter->second.getId()) +
                    "] Close (Disconnected from the server).");
        }
    }

    void Server::handleGUIClient(GUIIter iter)
    {
        try {
            iter->second.infoToRead();
        } catch (Shared::Connect::CloseException &_) {
            _connect.removeClient(iter->first);
            _clients.gui.erase(iter);
            Shared::Utils::logMsg(_logFile,
                "Client[" + std::to_string(iter->second.getId()) +
                    "] Close (Disconnected from the server).");
        }
    }

    std::optional<std::string> Server::getNewClientLine(
        std::unordered_map<int, NewClient>::iterator &iter)
    {
        bool close = false;

        try {
            Shared::Connect::receiveChunk(iter->first, iter->second.second);
        } catch (Shared::Connect::CloseException &_) {
            _connect.removeClient(iter->first);
            _clients.newClient.erase(iter);
            Shared::Utils::logMsg(_logFile,
                "Client[" + std::to_string(iter->second.first) +
                    "] Close (Disconnected from the server).");
            close = true;
        }
        std::optional<std::string> line;
        if (!close)
            line = Shared::Utils::parseLine(iter->second.second);
        return line;
    }

    void Server::handleNewClient(
        std::unordered_map<int, NewClient>::iterator &iter)
    {
        auto line = getNewClientLine(iter);
        if (line.has_value()) {
            if (line.value() == GRAPHIC) {
                _clients.gui.emplace(iter->first,
                    GUIClient(
                        iter->first, iter->second.first, _logFile, _env, _f));
                _clients.newClient.erase(iter);
                return;
            }
            auto find = _teams.find(line.value());
            if (find != _teams.end() && find->second > 0) {
                _env.addPlayer(iter->second.first, line.value(), find->second);
                _clients.ai.emplace(iter->first,
                    AIClient(iter->first,
                        iter->second.first,
                        find->first,
                        _logFile,
                        _env));
                find->second--;
                _clients.newClient.erase(iter);
            } else {
                Shared::Connect::send(iter->first, "ko\n");
                _connect.removeClient(iter->first);
                _clients.newClient.erase(iter);
                Shared::Utils::logMsg(_logFile,
                    "Client[" + std::to_string(iter->second.first) +
                        "] Close (Wrong Teams Selection).");
            }
        }
    }
    const std::vector<std::string> Server::DEFAULT_TEAMS = {"team1", "team2"};
}; // namespace Zappy
