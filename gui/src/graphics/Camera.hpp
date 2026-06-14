/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef CAMERA_HPP
    #define CAMERA_HPP
    #include <functional>
#include <raylib-cpp.hpp>
#include <unordered_map>

namespace Graphics {

    class Camera : public raylib::Camera {
    public:
        // using raylib::Camera::Camera;
        void update(float dt);
        void updateMouse();
        raylib::Vector3 alignToWorldPlane(raylib::Vector3 vector) const;
        void moveForward(float distance);
        void moveRight(float distance);
        void moveUp(float distance);
        void moveToTarget(float delta);
        raylib::Vector3 getForward() const;
        raylib::Vector3 getRight() const;

        void yaw(float angle);
        void roll(float angle);

        static constexpr auto CAMERA_MOVE_SPEED = 4.0;
        static constexpr KeyboardKey SPRINT_KEY = KEY_LEFT_SHIFT;
        static constexpr auto SPRINT_SCALE = 4;
        static constexpr auto WORLD_AXIS_THRESHOLD = 0.7071f;
        static constexpr auto MOUSE_MOVE_SENSITIVITY = 0.003f;

        using MovementMethod = std::function<void(Camera &, float)>;

        struct AxisMovementKeys {
            KeyboardKey negative;
            KeyboardKey positive;

            bool operator==(const AxisMovementKeys &) const = default;
        };

        static const std::unordered_map<AxisMovementKeys, MovementMethod>
            MOVEMENT_KEYS;
    };
} // namespace Graphics

template<>
struct std::hash<Graphics::Camera::AxisMovementKeys> {
    std::size_t operator()(
        const Graphics::Camera::AxisMovementKeys &k) const noexcept
    {
        std::size_t h1 = std::hash<int> {}((k.positive));
        std::size_t h2 = std::hash<int> {}((k.negative));

        return h1 ^ (h2 << 1);
    }
};

#endif
