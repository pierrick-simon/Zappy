/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef IGAMEOBJECT_HPP
    #define IGAMEOBJECT_HPP

    #include <raymath.h>

namespace Graphics {
    class Transformable3D {
    public:
        virtual ~Transformable3D() = default;
        virtual RayMath::Vector3 &getPosition();
        virtual RayMath::Quaternion &getRotation();
        virtual RayMath::Vector3 &getScale();
        [[nodiscard]] virtual const RayMath::Vector3 &getPosition() const;
        [[nodiscard]] virtual const RayMath::Quaternion &getRotation() const;
        [[nodiscard]] virtual const RayMath::Vector3 &getScale() const;
        [[nodiscard]] RayMath::Vector3 getForward() const;

    protected:
        Vector3 _position {};
        RayMath::Quaternion _rotation {};
        RayMath::Vector3 _scale {1, 1, 1};
    };
} // namespace Graphics

#endif
