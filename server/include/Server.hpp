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
    #include "Client.hpp"
    #include "Connect.hpp"
    #include "Environement.hpp"
    #include "GUIClient.hpp"
    #include "Utils.hpp"

namespace Zappy {
    class Server {
    public:
        Server(std::vector<std::string> args);
        ~Server();

        void run();

        static constexpr std::string_view HELP_FILE = "server/docs/help.txt";

    private:
        using AIIter = std::unordered_map<int, AIClient>::iterator;
        using GUIIter = std::unordered_map<int, GUIClient>::iterator;

        void infoToRead();
        bool update();
        void addClient();
        void handleClient(const std::vector<int> &);
        void handleDeadClient(const std::vector<int> &);
        void handleAIClient(AIIter);
        void handleGUIClient(GUIIter);
        void handleNewClient(std::unordered_map<int, NewClient>::iterator &);
        std::optional<std::string> getNewClientLine(
            std::unordered_map<int, NewClient>::iterator &);

        Shared::Connect _connect;
        std::unordered_map<std::string, std::size_t> _teams;
        std::vector<std::string> _teamsNames;

        Clients _clients;

        Shared::Clock _clock;
        int _timeout = -1;

        std::size_t _f;
        std::chrono::nanoseconds _fn;
        Environement _env;

        static bool RECEIVED_SIG_INT;

        std::ofstream _logFile;

        static constexpr std::string_view LOG_FILE = "server.log";
        static constexpr std::string_view GRAPHIC = "GRAPHIC";
        static constexpr std::size_t SECOND_IN_NANO = 1000000;
    };
} // namespace Zappy

#endif
