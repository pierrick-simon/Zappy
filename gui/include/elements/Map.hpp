/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include "Tile.hpp"
    #include "graphics/IDrawable3D.hpp"

namespace Zappy {
    class Map : public Graphics::IDrawable3D {
    public:
        bool updateSize(std::size_t x, std::size_t y);
        void updateTile(std::size_t x, std::size_t y,
            const std::vector<std::size_t> &resources);
        void setTilesPosition();

        [[nodiscard]] std::size_t getWidth() const
        {
            return _width;
        }
        [[nodiscard]] std::size_t getHeight() const
        {
            return _height;
        }

        void draw() const override;

    private:
        std::size_t _width = 0;
        std::size_t _height = 0;
        std::vector<Tile> _tiles;
        static constexpr auto TILE_WIDTH = 2;
        static constexpr auto TILE_HEIGHT = 2;
        static constexpr auto TILE_Y_POS = 0;
    };
} // namespace Zappy

#endif /* !MAP_HPP_ */
