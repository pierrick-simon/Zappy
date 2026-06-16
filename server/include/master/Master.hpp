/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Master
*/

#ifndef MASTER_HPP_
    #define MASTER_HPP_

    #include <string_view>
    #include "Client.hpp"
    #include "Process.hpp"

namespace Zappy {
    class Master {
    public:
        Master(int port, Clients &clients,
            std::unordered_map<std::string, std::size_t> &teams);

    private:
        int _port;
        Shared::Process _process;

        Clients &_clients;
        std::unordered_map<std::string, std::size_t> &_teams;

        static constexpr std::string_view IP = "127.0.0.1";
    };
} // namespace Zappy

#endif /* !MASTER_HPP_ */
