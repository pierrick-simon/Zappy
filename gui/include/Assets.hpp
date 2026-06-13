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
    static const std::filesystem::path RESOURCES_ROOT = "gui/resources";

    std::string GetResource(const std::string &file);
} // namespace Assets

#endif
