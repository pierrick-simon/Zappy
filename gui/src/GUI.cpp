/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** GUI
*/

#include "GUI.hpp"

namespace Zappy {
    GUI::GUI(int port, std::string ip) :
        _connect(port, ip)
    {
    }

    void GUI::run()
    {
        while (true);
    }
}
