/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Server
*/

#ifndef SERVER_HPP
    #define SERVER_HPP

    #include <fstream>
    #include <optional>
    #include <unordered_map>
    #include "AIClient.hpp"
    #include "Connect.hpp"
    #include "GUIClient.hpp"
    #include "Utils.hpp"

namespace Zappy {
    class Server {
    public:
        Server(int port, const std::vector<std::string> &teams,
            std::size_t nbPerTeams);
        ~Server();

        void run();

    private:
        using NewClient = std::pair<std::size_t, std::string>;
        using AIIter = std::unordered_map<int, AIClient>::iterator;
        using GUIIter = std::unordered_map<int, GUIClient>::iterator;

        void infoToRead();
        void update();
        void addClient();
        void handleClient(const std::vector<int> &);
        void handleAIClient(AIIter);
        void handleGUIClient(GUIIter);
        void handleNewClient(std::unordered_map<int, NewClient>::iterator &);
        std::optional<std::string> getNewClientLine(
            std::unordered_map<int, NewClient>::iterator &);

        Shared::Connect _connect;
        std::unordered_map<std::string, std::size_t> _teams;
        std::unordered_map<int, NewClient> _newClients;
        std::unordered_map<int, AIClient> _aiClients;
        std::unordered_map<int, GUIClient> _guiClients;

        Shared::Clock _clock;

        std::size_t x = 100;
        std::size_t y = 100;

        static bool RECEIVED_SIG_INT;

        std::ofstream _logFile;

        static constexpr std::string_view LOG_FILE = "server.log";
        static constexpr std::string_view GRAPHIC = "GRAPHIC";
    };
} // namespace Zappy

#endif
