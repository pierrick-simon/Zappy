/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUI
*/

#ifndef GUI_HPP
    #define GUI_HPP

    #include <fstream>
    #include <iomanip>
    #include <string>
    #include "Environement.hpp"
    #include "Window.hpp"

namespace Zappy {
    class GUI {
    public:
        GUI(std::vector<std::string> args);
        ~GUI();

        void run();

        static constexpr std::string_view HELP_FILE = "gui/docs/help.txt";

    private:
        void update();

        bool _isConnect = false;

        Environement _env;
        Graphics::Window _window;

        std::ofstream _logFile;

        static constexpr std::string_view LOG_FILE = "gui.log";
        static constexpr std::string_view DEFAULT_HOST = "127.0.0.1";
        static constexpr int DEFAULT_PORT = 8080;
    };
} // namespace Zappy

#endif
