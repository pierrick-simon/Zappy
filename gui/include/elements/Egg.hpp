/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Egg
*/

#ifndef EGG_HPP
    #define EGG_HPP

    #include "graphics/IDrawable3D.hpp"
    #include "graphics/Transformable3D.hpp"
    #include "Model.hpp"
    #include <Vector2.hpp>
    #include <fstream>

namespace Zappy {
    class Egg : public Graphics::IDrawable3D,
                public Graphics::Transformable3D {
    public:
        Egg(std::size_t x, std::size_t y, std::string team,
            raylib::Vector2 pos, raylib::Model &eggModel);

        [[nodiscard]] std::string getTeam() const
        {
            return _team;
        }

        [[nodiscard]] std::size_t getTile(std::size_t mapWidth) const;

        void draw3D() const;

        void initPos(std::size_t width, std::size_t height);

    private:
        std::size_t _x;
        std::size_t _y;
        std::string _team;
        raylib::Model &_eggModel;

        static constexpr float EGG_SCALE = 0.01;
    };
} // namespace Zappy

#endif
