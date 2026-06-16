/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Master
*/

#include "Master.hpp"

namespace Zappy {
    Master::Master(int port, Clients &clients,
        std::unordered_map<std::string, std::size_t> &teams) :
        _port(port), _clients(clients), _teams(teams)
    {
        _process.add("./zappy_gui", {});
    }
} // namespace Zappy
