/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUI
*/

#ifndef GUI_HPP
    #define GUI_HPP

    #include <fstream>
    #include <functional>
    #include <iomanip>
    #include <queue>
    #include <string>
    #include <unordered_map>
    #include "Connect.hpp"

namespace Zappy {
    class GUI {
    public:
        GUI(std::vector<std::string> args);

        void run();

        static constexpr std::string_view HELP_FILE = "gui/docs/help.txt";

    private:
        using Command = std::function<void(GUI &, std::istringstream &)>;

        bool infoToRead();
        bool connect();
        void update();

        Shared::Connect _connect;
        std::string _buffer;
        std::queue<std::string> _command;
        bool _isConnect = false;

        std::ofstream _logFile;

        static const std::unordered_map<std::string, Command> COMMANDS;

        static constexpr std::string_view LOG_FILE = "gui.log";
    };
} // namespace Zappy

#endif
