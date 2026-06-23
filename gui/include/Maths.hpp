/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef MATHS_HPP
    #define MATHS_HPP
    #include <numbers>
namespace Maths {
    constexpr float DegToRad(float deg)
    {
        return deg * (std::numbers::pi / 180.0f);
    }
    constexpr float RadToDeg(float rad)
    {
        return rad * (180.0f / std::numbers::pi);
    }
} // namespace Maths
#endif
