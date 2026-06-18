/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef TRANSFORMABLE_3D_HPP
    #define TRANSFORMABLE_3D_HPP
    #include <Vector3.hpp>
    #include <Vector4.hpp>

namespace Graphics {
    class Transformable3D {
    public:
        virtual ~Transformable3D() = default;
        virtual raylib::Vector3 &getPosition();
        virtual raylib::Quaternion &getRotation();
        virtual raylib::Vector3 &getScale();
        [[nodiscard]] virtual const raylib::Vector3 &getPosition() const;
        [[nodiscard]] virtual const raylib::Quaternion &getRotation() const;
        [[nodiscard]] virtual const raylib::Vector3 &getScale() const;
        [[nodiscard]] raylib::Vector3 getForward() const;

    protected:
        raylib::Vector3 _position {0, 0, 0};
        raylib::Quaternion _rotation = raylib::Quaternion::FromEuler(0, 0, 0);
        raylib::Vector3 _scale {1, 1, 1};
    };
} // namespace Graphics

#endif
