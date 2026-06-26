/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef MATHS_HPP
    #define MATHS_HPP
    #include <cmath>
    #include <numbers>

namespace Maths {
    constexpr float DegToRad(float deg)
    {
        return deg * (std::numbers::pi_v<float> / 180.0f);
    }

    constexpr float RadToDeg(float rad)
    {
        return rad * (180.0f / std::numbers::pi_v<float>);
    }

    constexpr float easeInOutSine(float value)
    {
        return -(std::cos(std::numbers::pi_v<float> * value) - 1) / 2;
    }

} // namespace Maths
#endif
