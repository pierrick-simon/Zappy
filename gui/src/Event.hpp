/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef EVENT_HPP
    #define EVENT_HPP
    #include <raylib.h>
    #include <utility>
    #include <variant>

namespace Graphics {

    class Pressed {};
    class PressedRepeat {};
    class Released {};

    using Event = std::variant<Pressed, PressedRepeat, Released>;

    using KeyEvent = std::pair<Event, KeyboardKey>;

} // namespace Graphics

#endif
