/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Main
*/

#include <iostream>
#include "Utils.hpp"
#include "Server.hpp"
#include "ServerException.hpp"

int main()
{
    try {
        Zappy::Server server(4242, {"first"}, 2);
        server.run();
    } catch (Shared::SharedException &e) {
        std::cerr << e.what() << std::endl;
        return Shared::EPIERROR;
    } catch (Zappy::ServerException &e) {
        std::cerr << e.what() << std::endl;
        return Shared::EPIERROR;
    }
    return Shared::EPISUCCESS;
}
