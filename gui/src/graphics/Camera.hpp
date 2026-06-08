/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef CAMERA_H
    #define CAMERA_H
    #include "GameObject.hpp"

namespace Graphics {
    class Camera : public Transformable3D {
    public:
        explicit Camera(double fov = DEFAULT_FOV);
        [[nodiscard]] double getFov() const;
        void setFov(double fov);

    private:
        double _fov;
        static constexpr auto DEFAULT_FOV = 60.0;
    };
} // namespace Graphics

#endif
