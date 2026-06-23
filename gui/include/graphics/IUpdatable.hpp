/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef UPDATABLE_HPP
    #define UPDATABLE_HPP

namespace Graphics {
    class IUpdatable {
    public:
        virtual ~IUpdatable() = default;
        virtual void update(float dt) = 0;
    };
} // namespace Graphics

#endif
