/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef UTILSVECTOR_HPP
    #define UTILSVECTOR_HPP
    #include <Vector3.hpp>

namespace Graphics::Vector3 {
    static constexpr raylib::Vector3 ZERO = {0, 0, 0};
    static constexpr raylib::Vector3 ONE = {1, 1, 1};
    static constexpr raylib::Vector3 RIGHT = {1, 0, 0};
    static constexpr raylib::Vector3 LEFT = {-1, 0, 0};
    static constexpr raylib::Vector3 UP = {0, 1, 0};
    static constexpr raylib::Vector3 DOWN = {0, -1, 0};
    static constexpr raylib::Vector3 FORWARD = {0, 0, 1};
    static constexpr raylib::Vector3 BACKWARD = {0, 0, -1};
} // namespace Graphics::Vector3
#endif
