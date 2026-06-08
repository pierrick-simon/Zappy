/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef CUBE_HPP
    #define CUBE_HPP
    #include "GameObject.hpp"

namespace Graphics {
    class Cube : public GameObject {
    public:
        explicit Cube() = default;

    protected:
        void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        static constexpr auto DEFAULT_SIZE = 1;
    };
} // namespace Graphics

#endif
