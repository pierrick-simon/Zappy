/*
** EPITECH PROJECT, 2026
** RayTracer
** File description:
** DESCRIPTION
*/

#include "Color.hpp"

#include <algorithm>
#include <cmath>

namespace Maths {
    Color::Color() :
        Color(BLACK)
    {
    }

    Color::Color(double r, double g, double b, double a) :
        Vector(r, g, b, a)
    {
    }
    Color::Color(const Vector3D &color, double a) :
        Vector(color.getX(), color.getY(), color.getZ(), a)
    {
    }
    Color::Color(const Vector &vector) :
        Vector(vector)
    {
    }
    Color Color::from8Bit(
        unsigned char r, unsigned char g, unsigned char b, unsigned char a)
    {
        return {r / 255.0, g / 255.0, b / 255.0, a / 255.0};
    }
    const Color Color::WHITE {1.0, 1.0, 1.0, 1.0};

    const Color Color::BLACK {0.0, 0.0, 0.0, 1.0};

    const Color Color::RED {1.0, 0.0, 0.0, 1.0};

    const Color Color::GREEN {0.0, 1.0, 0.0, 1.0};

    const Color Color::BLUE {0.0, 0.0, 1.0, 1.0};

    static unsigned char doubleToByte(double val)
    {
        val = std::clamp(val, 0.0, 1.0);
        return static_cast<unsigned char>(std::lround(val * 255.0));
    }

    Vector<4, unsigned char> Color::to8Bit() const
    {
        return Vector<4, unsigned char>(doubleToByte(getR()),
            doubleToByte(getG()),
            doubleToByte(getB()),
            doubleToByte(getA()));
    }

    double &Color::getR()
    {
        return getX();
    }

    const double &Color::getR() const
    {
        return getX();
    }

    double &Color::getG()
    {
        return getY();
    }

    const double &Color::getG() const
    {
        return getY();
    }

    double &Color::getB()
    {
        return getZ();
    }

    const double &Color::getB() const
    {
        return getZ();
    }

    double &Color::getA()
    {
        return getW();
    }

    const double &Color::getA() const
    {
        return getW();
    }

    Color &Color::operator*=(const Vector3D &other)
    {
        this->getR() *= other.getX();
        this->getG() *= other.getY();
        this->getB() *= other.getZ();
        this->clamp();
        return *this;
    }

    Color &Color::operator*=(const Color &other)
    {
        this->getR() *= other.getR();
        this->getG() *= other.getG();
        this->getB() *= other.getB();
        this->getA() *= other.getA();
        return *this;
    }

    Color &Color::operator*=(const double &other)
    {
        this->getR() *= other;
        this->getG() *= other;
        this->getB() *= other;
        this->clamp();
        return *this;
    }

    Color &Color::operator+=(const Vector3D &other)
    {
        this->getR() += other.getX();
        this->getG() += other.getY();
        this->getB() += other.getZ();
        this->clamp();
        return *this;
    }

    Color &Color::operator+=(const double &other)
    {
        this->getR() += other;
        this->getG() += other;
        this->getB() += other;
        this->clamp();
        return *this;
    }

    Color &Color::operator+=(const Vector &other)
    {
        this->getR() += other.getX();
        this->getG() += other.getY();
        this->getB() += other.getZ();
        this->getA() += other.getW();
        this->clamp();
        return *this;
    }

    Color::Color(const Color &other) :
        Vector(other)
    {
    }

    Color &Color::operator=(const Color &other)
    {
        if (this == &other)
            return *this;
        Vector::operator=(other);
        return *this;
    }

    Color &Color::operator=(const Vector3D &vector)
    {
        this->getR() = vector.getX();
        this->getG() = vector.getY();
        this->getB() = vector.getZ();
        this->clamp();
        return *this;
    }

    Color &Color::clamp()
    {
        this->getR() = std::clamp(this->getR(), 0.0, 1.0);
        this->getG() = std::clamp(this->getG(), 0.0, 1.0);
        this->getB() = std::clamp(this->getB(), 0.0, 1.0);
        this->getA() = std::clamp(this->getA(), 0.0, 1.0);
        return *this;
    }

    Color Color::operator/(const double &other) const
    {
        return Color(this->getR() / other,
            this->getG() / other,
            this->getB() / other,
            this->getA() / other);
    }

    Color Color::mean(std::vector<Color> colors)
    {
        Maths::Color finalColor = Maths::Color::BLACK;
        for (auto color : colors) {
            finalColor.getX() += color.getX();
            finalColor.getY() += color.getY();
            finalColor.getZ() += color.getZ();
            finalColor.getW() += color.getW();
        }
        return finalColor / static_cast<double>(colors.size());
    }
} // namespace Maths
