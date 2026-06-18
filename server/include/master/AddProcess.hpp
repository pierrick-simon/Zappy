/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** AddProcess
*/

#ifndef ADDPROCESS_HPP_
    #define ADDPROCESS_HPP_

    #include <vector>
    #include "Client.hpp"
    #include "Process.hpp"

namespace Zappy {
    class AddProcess {
    public:
        AddProcess(int port, Clients &clients);

        void addGui();
        void addAi(const std::string &team, const std::string &algo);
        void addAi(
            const std::string &team, const std::vector<std::string> &algos);

    private:
        int _port;
        Shared::Process _process;

        Clients &_clients;

        static constexpr std::string_view IP = "127.0.0.1";
        static constexpr std::string_view AI_EXEC = "./zappy_ai";
        static constexpr std::string_view GUI_EXEC = "./zappy_gui";
    };
} // namespace Zappy

#endif /* !ADDPROCESS_HPP_ */
