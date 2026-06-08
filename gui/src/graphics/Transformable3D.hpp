/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef IGAMEOBJECT_HPP
    #define IGAMEOBJECT_HPP
    #include "../maths/Quaternion.hpp"

namespace Graphics {
    class Transformable3D {
    public:
        virtual ~Transformable3D() = default;
        virtual Maths::Vector3D &getPosition();
        virtual Maths::Quaternion &getRotation();
        virtual Maths::Vector3D &getScale();
        [[nodiscard]] virtual const Maths::Vector3D &getPosition() const;
        [[nodiscard]] virtual const Maths::Quaternion &getRotation() const;
        [[nodiscard]] virtual const Maths::Vector3D &getScale() const;
        [[nodiscard]] Maths::Vector3D getForward() const;

    protected:
        Maths::Vector3D _position;
        Maths::Quaternion _rotation;
        Maths::Vector3D _scale {1, 1, 1};
    };
} // namespace Graphics

#endif
