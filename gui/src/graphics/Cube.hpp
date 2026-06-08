/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef CUBE_HPP
    #define CUBE_HPP
    #include "GlGameObject.hpp"

namespace Graphics {
    class Cube : public GLGameObject {
    public:
        explicit Cube() = default;

    protected:
        void glDraw() const override;

    private:
        static constexpr auto DEFAULT_SIZE = 1;
    };
} // namespace Graphics

#endif
