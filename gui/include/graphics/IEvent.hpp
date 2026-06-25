/*
** EPITECH PROJECT, 2026
** gui
** File description:
** IEvent
*/

#ifndef IEVENT_HPP_
    #define IEVENT_HPP_

    #include <raylib-cpp.hpp>

namespace Graphics {
    class IEvent {
    public:
        virtual ~IEvent() = default;
        virtual void event(raylib::Camera3D &camera,
            const raylib::Vector2 &mouse, const Ray &ray, bool &leftClick) = 0;
    };
} // namespace Graphics

#endif /* !IEVENT_HPP_ */
