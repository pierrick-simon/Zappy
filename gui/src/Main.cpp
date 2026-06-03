/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Main
*/

#include <iostream>
#include "Utils.hpp"
#include "GUI.hpp"
#include "GUIException.hpp"

int main()
{
    try {
        Zappy::GUI gui(4242, "127.0.0.1");
        gui.run();
    } catch (Shared::SharedException &e) {
        std::cerr << e.what() << std::endl;
        return Shared::EPIERROR;
    } catch (Zappy::GUIException &e) {
        std::cerr << e.what() << std::endl;
        return Shared::EPIERROR;
    }
    return Shared::EPISUCCESS;
}

