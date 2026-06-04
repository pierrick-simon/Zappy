/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUI
*/

#ifndef GUI_HPP
    #define GUI_HPP

    #include <string>
    #include <fstream>
    #include <queue>
    #include "Connect.hpp"

namespace Zappy {
    class GUI {
        public:
            GUI(int port, std::string ip);

            void run();

        private:
            bool infoToRead();
            bool connect();
            bool handleCommand();

            Shared::Connect _connect;
            std::string _buffer;
            std::queue<std::string> _command;
            bool _isConnect = false;

            std::ofstream _logFile;

            static constexpr std::string_view LOG_FILE = "gui.log";
    };
}

#endif
