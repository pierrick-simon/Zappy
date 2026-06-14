/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Client
*/

#ifndef CLIENT_HPP
    #define CLIENT_HPP

    #include <string>
    #include <unordered_map>
    #include "AIClient.hpp"
    #include "GUIClient.hpp"

namespace Zappy {
    using NewClient = std::pair<std::size_t, std::string>;

    struct Clients {
        std::unordered_map<int, NewClient> newClient;
        std::unordered_map<int, AIClient> ai;
        std::unordered_map<int, GUIClient> gui;
    };
} // namespace Zappy

#endif
