/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AddProcess
*/

#include "AddProcess.hpp"

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
} // namespace Zappy
