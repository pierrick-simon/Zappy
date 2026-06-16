/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Environement
*/

#ifndef GUI_ENVIRONEMENT_HPP_
    #define GUI_ENVIRONEMENT_HPP_

    #include <functional>
    #include <queue>
    #include <string_view>
    #include <unordered_map>
    #include <vector>
    #include "Connect.hpp"
    #include "Egg.hpp"
    #include "Elevation.hpp"
    #include "Map.hpp"
    #include "Player.hpp"

namespace Zappy {
    class Environement {
    public:
        Environement(int port, const std::string &ip, std::ofstream &logFile,
            bool &isConnect);

        bool update();

    private:
        using Event = std::function<void(Environement &, std::istringstream &)>;

        struct Message {
            std::size_t id;
            std::string message;
        };

        bool connect();
        bool infoToRead();
        void handleEvents();

        Map _map;
        std::unordered_map<std::size_t, Player> _players;
        std::unordered_map<std::size_t, Egg> _eggs;
        std::vector<Elevation> _elevations;
        std::vector<std::string> _teams;
        std::queue<Message> _msg;
        std::size_t _timeUnit;

        Shared::Connect _connect;
        std::string _buffer;
        std::queue<std::string> _events;

        bool &_isConnect;
        std::ofstream &_logFile;
        static const std::unordered_map<std::string, Event> EVENTS;

        static constexpr std::string_view WELCOME = "WELCOME";
        static constexpr std::string_view TEAM = "GRAPHIC";
    };
} // namespace Zappy

#endif /* !ENVIRONEMENT_HPP_ */
