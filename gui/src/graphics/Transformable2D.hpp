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
        virtual void setPosition(raylib::Vector2 pos);
        virtual void setRotation(float rotation);
        virtual void setScale(raylib::Vector2 scale);
        virtual void setOrigin(raylib::Vector2 origin);
        [[nodiscard]] virtual const raylib::Vector2 &getPosition() const;
        [[nodiscard]] virtual const float &getRotation() const;
        [[nodiscard]] virtual const raylib::Vector2 &getScale() const;
        [[nodiscard]] virtual const raylib::Vector2 &getOrigin() const;

    protected:
        raylib::Vector2 _position {0, 0};
        float _rotation {0};
        raylib::Vector2 _scale {1, 1};
        raylib::Vector2 _origin {0, 0};
    };
} // namespace Graphics

#endif
