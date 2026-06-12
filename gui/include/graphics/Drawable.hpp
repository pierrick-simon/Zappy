/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef DRAWABLE_HPP
    #define DRAWABLE_HPP

namespace Graphics {
    class Drawable {
    public:
        virtual ~Drawable() = default;
        virtual void draw() const = 0;
    };
} // namespace Graphics

#endif
