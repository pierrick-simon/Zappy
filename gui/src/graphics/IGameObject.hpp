/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef IGAMEOBJECT_HPP
    #define IGAMEOBJECT_HPP
    #include "../maths/Vector.hpp"
    #include "../maths/Quaternion.hpp"

namespace Graphics
{
class IGameObject
{
public:
    virtual ~IGameObject() = default;
    virtual void render() const = 0;
    virtual Maths::Vector3D &getPosition() = 0;
    virtual Maths::Quaternion &getRotation() = 0;
    virtual Maths::Vector3D &getScale() = 0;
    [[nodiscard]] virtual const Maths::Vector3D &getPosition() const = 0;
    [[nodiscard]] virtual const Maths::Quaternion &getRotation() const = 0;
    [[nodiscard]] virtual const Maths::Vector3D &getScale() const = 0;
};
} // Graphics

#endif
