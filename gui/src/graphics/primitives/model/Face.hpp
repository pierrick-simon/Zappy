/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef FACE_HPP
    #define FACE_HPP
    #include <optional>
    #include "maths/Vector.hpp"

namespace Graphics {
    class Face {
        struct Point {
            Maths::Vector3D pos;
            std::optional<Maths::Vector3D> texturePos;
            std::optional<Maths::Vector3D> normalPos;
        };
    };
} // namespace Graphics

#endif
