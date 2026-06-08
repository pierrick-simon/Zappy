/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef COLOR_HPP
    #define COLOR_HPP
    
    #include <limits>
    #include <vector>

    #include "Vector.hpp"

namespace Maths {

    using Color8bit = Vector<4, unsigned char>;

    class Color : public Vector<4, double> {
    public:
        Color();

        Color(double r, double g, double b, double a = 1.0);

        explicit Color(const Vector3D &color, double a = 1.0);

        explicit Color(const Vector &vector);

        Color(const Color &other);

        Color &operator=(const Color &other);
        Color &operator=(const Vector3D &vector);

        static Color from8Bit(unsigned char r, unsigned char g,
            unsigned char b,
            unsigned char a = std::numeric_limits<unsigned char>::max());

        [[nodiscard]] Color8bit to8Bit() const;

        [[nodiscard]] double &getR();

        [[nodiscard]] const double &getR() const;

        [[nodiscard]] double &getG();

        [[nodiscard]] const double &getG() const;

        [[nodiscard]] double &getB();

        [[nodiscard]] const double &getB() const;

        [[nodiscard]] double &getA();

        [[nodiscard]] const double &getA() const;

        Color &operator*=(const Vector3D &other);

        Color &operator*=(const Color &other);

        Color &operator*=(const double &other);

        Color &operator+=(const Vector3D &other);

        Color &operator+=(const double &other);

        Color &operator+=(const Vector &other);

        Color operator/(const double &other) const;

        Color &clamp();

        static Color mean(std::vector<Color> colors);

        static const Color WHITE;

        static const Color BLACK;

        static const Color RED;

        static const Color GREEN;

        static const Color BLUE;
    };
} // Maths

#endif
