/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Server
*/

#ifndef SERVER_HPP
    #define SERVER_HPP

    #include <fstream>
    #include "Connect.hpp"

namespace Zappy {
    class Server {
        public:
            Server(int port);
            ~Server();

            void run();

        private:
            void logMsg(std::string);

            Shared::Connect _connect;

            static bool RECEIVED_SIG_INT;

            std::ofstream _logFile;
            static constexpr std::string_view LOG_FILE = "server.log";
    };
}

#endif
