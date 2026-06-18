/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef ASSETS_HPP
    #define ASSETS_HPP
    #include <filesystem>

namespace Assets {
    static constexpr std::string RESOURCES_ROOT = "gui/resources";

    constexpr auto getResource(const std::string &file)
    {
        return RESOURCES_ROOT + "/" + file;
    }
} // namespace Assets

#endif
