/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Sphere
*/

#ifndef SPHERE_HPP_
    #define SPHERE_HPP_

    #include <raylib-cpp.hpp>
    #include "graphics/IDrawable3D.hpp"
    #include "graphics/Transformable3D.hpp"

namespace Graphics {
    class Sphere : public Transformable3D, public IDrawable3D {
    public:
        Sphere(float radius = 0.f);

        void draw3D() const override;

        float &getRadius();
        [[nodiscard]] const float &getRadius() const;
        raylib::Color &getColor();
        [[nodiscard]] const raylib::Color &getColor() const;

    private:
        float _radius;
        raylib::Color _color;
    };
} // namespace Graphics

#endif /* !SPHERE_HPP_ */
