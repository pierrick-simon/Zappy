/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AddProcess
*/

#include "AddProcess.hpp"
#include <iostream>
#include <random>
#include <ranges>

namespace Zappy {
    AddProcess::AddProcess(int port, Clients &clients) :
        _port(port), _clients(clients)
    {
    }

    void AddProcess::addGui()
    {
        if (_clients.gui.empty())
            _process.add(GUI_EXEC.data(), {"-p", std::to_string(_port)});
    }

    void AddProcess::addAi(const std::string &team, const std::string &algo)
    {
        _process.add(AI_EXEC.data(),
            {"-p",
                std::to_string(_port),
                "-n",
                team,
                "-a",
                algo,
                "-h",
                "127.0.0.1"});
    }

    void AddProcess::addAi(
        const std::string &team, const std::vector<std::string> &algos)
    {
        if (algos.empty())
            return;
        auto algo = algos.begin();
        std::advance(algo, std::rand() % algos.size());
        _process.add(AI_EXEC.data(),
            {"-p",
                std::to_string(_port),
                "-n",
                team,
                "-a",
                *algo,
                "-h",
                "127.0.0.1"});
    }
} // namespace Zappy
