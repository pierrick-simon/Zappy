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
    };
} // namespace Zappy

#endif
