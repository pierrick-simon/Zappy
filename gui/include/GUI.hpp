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
#include "../src/Window.hpp"
    #include "Connect.hpp"

namespace Zappy {
    class GUI {
    public:
        GUI(int port, const std::string &ip);

        void run();

    private:
        using Command = std::function<void(GUI &, std::istringstream &)>;

        bool infoToRead();
        bool connect();
        void update();

        Shared::Connect _connect;
        std::string _buffer;
        std::queue<std::string> _command;
        bool _isConnect = false;

        Graphics::Window _window;

        std::ofstream _logFile;

        static const std::unordered_map<std::string, Command> COMMANDS;

        static constexpr std::string_view LOG_FILE = "gui.log";
    };
} // namespace Zappy

#endif
