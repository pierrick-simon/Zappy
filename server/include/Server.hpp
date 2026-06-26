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
    #include "Master.hpp"
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

        unsigned int initSeed(std::vector<std::string> args);
        void infoToRead();
        bool update();
        void updateEnv(std::chrono::milliseconds elapsed);
        void updateAi(std::chrono::milliseconds elapsed);
        void updateGui();
        void addClient();
        void handleClient(const std::vector<int> &);
        void handleDeadClient(const std::vector<int> &);
        void handleAIClient(AIIter);
        void handleGUIClient(GUIIter);
        void handleNewClient(std::unordered_map<int, NewClient>::iterator &);
        std::optional<std::string> getNewClientLine(
            std::unordered_map<int, NewClient>::iterator &);

        int _port;
        Shared::Connect _connect;
        std::unordered_map<std::string, std::size_t> _teams;
        std::vector<std::string> _teamsNames;

        Clients _clients;

        Shared::Clock _clock;
        int _timeout = -1;
        unsigned int _seed = 0;

        std::size_t _f;
        Environement _env;

        static bool RECEIVED_SIG_INT;

        std::ofstream _logFile;

        std::optional<Master> _master;

        static constexpr std::string_view LOG_FILE = "server.log";
        static constexpr std::string_view GRAPHIC = "GRAPHIC";
        static const std::vector<std::string> DEFAULT_TEAMS;
        static constexpr int DEFAULT_PORT = 8080;
        static constexpr std::size_t DEFAULT_FREQ = 100;
        static constexpr std::size_t DEFAULT_X = 100;
        static constexpr std::size_t DEFAULT_Y = 100;
    };
} // namespace Zappy

#endif
