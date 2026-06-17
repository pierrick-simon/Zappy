/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef IDRAWABLE2D_HPP
    #define IDRAWABLE2D_HPP
namespace Graphics {
    class IDrawable2D {
    public:
        virtual ~IDrawable2D() = default;
        virtual void draw() const = 0;
    };
} // namespace Graphics
#endif