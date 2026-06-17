/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef IGAMEOBJECT_HPP
    #define IGAMEOBJECT_HPP
    #include <Vector2.hpp>
    #include <Vector4.hpp>

namespace Graphics {
    class Transformable2D {
    public:
        virtual ~Transformable2D() = default;
        virtual raylib::Vector2 &getPosition();
        virtual raylib::Quaternion &getRotation();
        virtual raylib::Vector2 &getScale();
        [[nodiscard]] virtual const raylib::Vector2 &getPosition() const;
        [[nodiscard]] virtual const raylib::Quaternion &getRotation() const;
        [[nodiscard]] virtual const raylib::Vector2 &getScale() const;

    protected:
        raylib::Vector2 _position {0, 0};
        raylib::Quaternion _rotation = raylib::Quaternion::FromEuler(0, 0, 0);
        raylib::Vector2 _scale {1, 1};
    };
} // namespace Graphics

#endif
