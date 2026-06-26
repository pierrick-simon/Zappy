/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Camera.hpp"

#include <algorithm>

namespace Graphics {
    void Camera::update(float dt)
    {
        float cameraMoveSpeed = CAMERA_MOVE_SPEED * dt;
        if (IsKeyDown(SPRINT_KEY))
            cameraMoveSpeed *= SPRINT_SCALE;

        for (const auto &[keys, method] : MOVEMENT_KEYS) {
            if (IsKeyDown(keys.positive))
                method(*this, cameraMoveSpeed);
            if (IsKeyDown(keys.negative))
                method(*this, -cameraMoveSpeed);
        }

        if (raylib::Mouse::IsButtonDown(ROTATE_BUTTON))
            this->updateMouse();
        this->moveToTarget(-raylib::Mouse::GetWheelMove());
    }

    void Camera::updateMouse()
    {
        raylib::Vector2 mousePosDelta = raylib::Mouse::GetDelta();

        this->yaw(-mousePosDelta.x * MOUSE_MOVE_SENSITIVITY);
        this->roll(-mousePosDelta.y * MOUSE_MOVE_SENSITIVITY);
    }

    raylib::Vector3 Camera::alignToWorldPlane(raylib::Vector3 vector) const
    {
        if (fabsf(this->up.z) > WORLD_AXIS_THRESHOLD)
            vector.z = 0;
        else if (fabsf(this->up.x) > WORLD_AXIS_THRESHOLD)
            vector.x = 0;
        else
            vector.y = 0;

        return vector.Normalize();
    }

    void Camera::moveForward(float distance)
    {
        auto forward = alignToWorldPlane(this->getForward());

        raylib::Vector3 delta = forward * distance;
        this->position = raylib::Vector3(this->position) + delta;
        this->target = raylib::Vector3(this->target) + delta;
    }

    void Camera::moveRight(float distance)
    {
        auto right = alignToWorldPlane(this->getRight());

        right = right * distance;
        this->position = raylib::Vector3(this->position) + right;
        this->target = raylib::Vector3(this->target) + right;
    }

    void Camera::moveUp(float distance)
    {
        raylib::Vector3 up(this->GetUp());

        up *= distance;
        this->position = raylib::Vector3(this->position) + up;
        this->target = raylib::Vector3(this->target) + up;
    }

    void Camera::moveToTarget(float delta)
    {
        float distance =
            raylib::Vector3(this->GetPosition()).Distance(this->GetTarget());

        distance += delta;
        distance = std::max(distance, 0.001f);

        auto forward = this->getForward();
        this->SetPosition(
            raylib::Vector3(this->GetTarget()) + forward * -distance);
    }

    raylib::Vector3 Camera::getForward() const
    {
        return (raylib::Vector3(this->target) - raylib::Vector3(this->position))
            .Normalize();
    }

    raylib::Vector3 Camera::getRight() const
    {
        raylib::Vector3 forward = this->getForward();
        raylib::Vector3 up = this->GetUp();

        return forward.CrossProduct(up).Normalize();
    }

    void Camera::yaw(float angle)
    {
        raylib::Vector3 up(this->GetUp());
        auto targetPosition =
            raylib::Vector3(this->GetTarget()) - this->GetPosition();
        targetPosition = Vector3RotateByAxisAngle(targetPosition, up, angle);
        this->position = raylib::Vector3(this->GetTarget()) - targetPosition;
    }

    void Camera::roll(float angle)
    {
        raylib::Vector3 up(this->GetUp());
        auto targetPosition =
            raylib::Vector3(this->GetTarget()) - this->GetPosition();

        float maxAngleUp = Vector3Angle(up, targetPosition) -
            std::numeric_limits<float>::epsilon();
        float maxAngleDown = -Vector3Angle(-up, targetPosition) +
            std::numeric_limits<float>::epsilon();
        angle = std::ranges::clamp(angle, maxAngleDown, maxAngleUp);

        auto right = this->getRight();
        targetPosition = Vector3RotateByAxisAngle(targetPosition, right, angle);
        this->position = raylib::Vector3(this->GetTarget()) - targetPosition;
    }

    const std::unordered_map<Camera::AxisMovementKeys, Camera::MovementMethod>
        Camera::MOVEMENT_KEYS = {
            {{KEY_S, KEY_W}, {&Camera::moveForward}},
            {{KEY_A, KEY_D}, {&Camera::moveRight}},
            {{KEY_Q, KEY_E}, {&Camera::moveUp}},
    };
} // namespace Graphics
