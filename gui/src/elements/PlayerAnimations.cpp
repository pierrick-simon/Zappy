/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "PlayerAnimations.hpp"

#include <algorithm>
#include <cmath>

namespace Zappy::PlayerAnimations {
    float getNextFrame(
        WrapMode mode, float frameTime, size_t keyframeCount, float fps)
    {
        if (keyframeCount == 0 || fps <= 0.0f)
            return 0.0f;

        const float animationDuration = static_cast<float>(keyframeCount) / fps;

        const float lastFrameTime = static_cast<float>(keyframeCount - 2) / fps;

        if (mode == CLAMP)
            return std::clamp(frameTime, 0.0f, lastFrameTime);

        if (mode == LOOP) {
            float wrapped = std::fmod(frameTime, animationDuration);
            return wrapped < 0.0f ? wrapped + animationDuration : wrapped;
        }

        return frameTime;
    }
} // namespace Zappy::PlayerAnimations
