/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Server
*/

#ifndef SERVER_HPP
    #define SERVER_HPP

    #include "Connect.hpp"

namespace Zappy {
    class Server {
        public:
            Server(int port);

            void run();

        private:
            static bool RECEIVED_SIG_INT;
            Shared::Connect _connect;
    };
}

#endif
