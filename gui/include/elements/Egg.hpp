/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Egg
*/

#ifndef EGG_HPP
    #define EGG_HPP

    #include <Vector2.hpp>
    #include <fstream>
    #include "Model.hpp"
    #include "Tile.hpp"
    #include "graphics/IDrawable3D.hpp"
    #include "graphics/Transformable3D.hpp"

namespace Zappy {
    class Egg : public Graphics::IDrawable3D, public Graphics::Transformable3D {
    public:
        Egg(std::size_t x, std::size_t y, std::string team, raylib::Vector2 pos,
            raylib::Model &eggModel);

        [[nodiscard]] std::string getTeam() const
        {
            return _team;
        }

        [[nodiscard]] std::size_t getTile(std::size_t mapWidth) const;
        void draw3D() const override;

        void initPos(std::size_t width, std::size_t height);

    private:
        std::size_t _x;
        std::size_t _y;
        std::string _team;
        raylib::Model &_eggModel;

        static constexpr float EGG_SCALE = 0.01;
        static constexpr float EGG_SCALE_MODIFIER = 0.2;
        static constexpr raylib::Vector2 RANGE = raylib::Vector2 {
            (Tile::TILE_SIZE.x / 2.0) - Tile::TILE_PADDING * Tile::TILE_SIZE.x,
            (Tile::TILE_SIZE.y / 2.0) - Tile::TILE_PADDING *Tile::TILE_SIZE.y};
    };
} // namespace Zappy

#endif
