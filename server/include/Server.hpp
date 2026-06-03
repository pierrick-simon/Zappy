/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Server
*/

#ifndef SERVER_HPP
    #define SERVER_HPP

    #include <fstream>
    #include <unordered_map>
    #include "Connect.hpp"
    #include "AIClient.hpp"
    #include "GUIClient.hpp"

namespace Zappy {
    class Server {
        public:
            Server(int port, std::vector<std::string> teams, std::size_t nbPerTeams);
            ~Server();

            void run();

        private:
            void logMsg(std::string);
            void addClient();
            void handleClient(const std::vector<int> &);
            void handleNewClient(std::unordered_map<int, std::string>::iterator &);

            Shared::Connect _connect;
            std::unordered_map<std::string, std::size_t> _teams;
            std::unordered_map<int, std::string> _newClients;
            std::unordered_map<int, AIClient> _AIClients;
            std::unordered_map<int, GUIClient> _GUIClients;

            std::size_t x = 100;
            std::size_t y = 100;
            
            static bool RECEIVED_SIG_INT;

            std::ofstream _logFile;

            static constexpr std::string_view LOG_FILE = "server.log";
            static constexpr std::string_view GRAPHIC = "GRAPHIC";
    };
}

#endif
