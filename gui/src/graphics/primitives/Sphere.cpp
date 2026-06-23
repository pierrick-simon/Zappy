/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Sphere
*/

#include "Sphere.hpp"

namespace Graphics {
    Sphere::Sphere(float radius) : _radius(radius)
    {
    }

    void Sphere::draw3D() const
    {
        DrawSphere(this->_position, this->_radius, this->_color);
    }

    float &Sphere::getRadius()
    {
        return _radius;
    }

    [[nodiscard]] const float &Sphere::getRadius() const
    {
        return _radius;
    }

    raylib::Color &Sphere::getColor()
    {
        return this->_color;
    }

    const raylib::Color &Sphere::getColor() const
    {
        return this->_color;
    }
}
