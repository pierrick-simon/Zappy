/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef IDRAWABLE3D_HPP
    #define IDRAWABLE3D_HPP
namespace Graphics {
    class IDrawable3D {
    public:
        virtual ~IDrawable3D() = default;
        virtual void draw() const = 0;
    };
} // namespace Graphics
#endif
