/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef PLAYERANIMATIONS_HPP
    #define PLAYERANIMATIONS_HPP

    #include <cstddef>

namespace Zappy::PlayerAnimations {
    enum WrapMode { LOOP, CLAMP };

    struct Animation {
        char const *name;
        WrapMode wrapMode;
    };

    static constexpr Animation IDLE = {"Idle", LOOP};
    static constexpr Animation WALKING = {"Walking", LOOP};
    static constexpr Animation DIGGING_UP = {"DiggingUp", CLAMP};
    static constexpr Animation DIGGING_DOWN = {"DiggingDown", CLAMP};

    float getNextFrame(
        WrapMode mode, float frameTime, size_t keyframeCount, float fps);
} // namespace Zappy::PlayerAnimations
#endif
