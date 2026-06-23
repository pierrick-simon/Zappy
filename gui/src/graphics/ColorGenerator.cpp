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
        raylib::Color c = hsvToColor(_current, SATURATION, VALUE);
        _current = std::fmod(_current + GOLDEN_RATIO, 1.0f);
        return c;
    }

    raylib::Color ColorGenerator::hsvToColor(
        float current, float saturation, float value)
    {
        int i = static_cast<int>(current * 6.0f);
        float f = current * 6.0f - float(i);
        float p = value * (1.0f - saturation);
        float q = value * (1.0f - f * saturation);
        float t = value * (1.0f - (1.0f - f) * saturation);
        auto color = raylib::Color::White();

        switch (i % 6) {
            case 0:
                color = makeColor(value, t, p);
                break;
            case 1:
                color = makeColor(q, value, p);
            case 2:
                color = makeColor(p, value, t);
                break;
            case 3:
                color = makeColor(p, q, value);
                break;
            case 4:
                color = makeColor(t, p, value);
                break;
            default:
                color = makeColor(value, p, q);
                break;
        }
        return color;
    }

    raylib::Color ColorGenerator::makeColor(float r, float g, float b)
    {
        return raylib::Color {static_cast<unsigned char>(r * 255),
            static_cast<unsigned char>(g * 255),
            static_cast<unsigned char>(b * 255),
            255};
    }
} // namespace Graphics
