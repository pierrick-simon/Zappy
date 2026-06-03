/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUI
*/

#ifndef GUI_HPP
    #define GUI_HPP

    #include <string>
    #include "Connect.hpp"

namespace Zappy {
    class GUI {
        public:
            GUI(int port, std::string ip);

            void run();
        private:
            Shared::Connect _connect;
    };
}

#endif
