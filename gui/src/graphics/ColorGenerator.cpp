/*
** EPITECH PROJECT, 2026
** gui
** File description:
** ColorGenerator
*/

#include "graphics/ColorGenerator.hpp"

namespace Graphics {
    raylib::Color ColorGenerator::next()
    {
        auto c = raylib::Color::FromHSV(_current, SATURATION, VALUE);
        _current = std::fmod(_current + GOLDEN_RATIO, 1.0f);
        return c;
    }
} // namespace Graphics
