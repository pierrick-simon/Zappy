/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Assets.hpp"

namespace Assets {
    std::string getResource(const std::string &file)
    {
        return (RESOURCES_ROOT / file).string();
    }
} // namespace Assets
