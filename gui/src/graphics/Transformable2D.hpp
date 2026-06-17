/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef TRANSFORMABLE_2D_HPP
    #define TRANSFORMABLE_2D_HPP
    #include <Vector2.hpp>

namespace Graphics {
    class Transformable2D {
    public:
        virtual ~Transformable2D() = default;
        virtual raylib::Vector2 &getPosition();
        virtual float &getRotation();
        virtual raylib::Vector2 &getScale();
        [[nodiscard]] virtual const raylib::Vector2 &getPosition() const;
        [[nodiscard]] virtual const float &getRotation() const;
        [[nodiscard]] virtual const raylib::Vector2 &getScale() const;

    protected:
        raylib::Vector2 _position {0, 0};
        float _rotation {0};
        raylib::Vector2 _scale {1, 1};
    };
} // namespace Graphics

#endif
