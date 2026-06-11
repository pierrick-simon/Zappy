/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef CAMERA_H
    #define CAMERA_H
    #include "RayLib.hpp"

namespace Graphics {
    class Camera : RayLib::Camera {
    public:
        explicit Camera(float fov = DEFAULT_FOV);

    private:
        static constexpr auto DEFAULT_FOV = 60.0;
    };
} // namespace Graphics

#endif
