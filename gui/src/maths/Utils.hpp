/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef UTILS_HPP
    #define UTILS_HPP
#include <numbers>
    #include <type_traits>

namespace Maths {
    template<typename T>
        requires std::is_arithmetic_v<T>
    constexpr T invertedLerp(
        const T &min, const T &max, const T &value) noexcept
    {
        return (value - min) / (max - min);
    }

    constexpr auto toRadians(auto v)
    {
        return v * (std::numbers::pi / static_cast<decltype(v)>(180.0));
    }
} // namespace Maths

#endif
