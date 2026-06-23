/*
** EPITECH PROJECT, 2026
** gui
** File description:
** ColorGenerator
*/

#ifndef COLORGENERATOR_HPP_
    #define COLORGENERATOR_HPP_

    #include "graphics/AShadered.hpp"

namespace Graphics {
    class ColorGenerator {
    public:
        raylib::Color next();

    private:
        static raylib::Color hsvToColor(
            float current, float saturation, float value);
        static raylib::Color makeColor(float r, float g, float b);

        float _current = 0.0f;

        static constexpr float GOLDEN_RATIO = 1.618033988749895f;
        static constexpr float SATURATION = 0.72f;
        static constexpr float VALUE = 0.92f;
    };
} // namespace Graphics

#endif /* !COLORGENERATOR_HPP_ */
