/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include "Info.hpp"
    #include "InfoBox.hpp"
    #include "Tile.hpp"
    #include "graphics/AShadered.hpp"
    #include "graphics/IDrawable3D.hpp"

namespace Zappy {
    class Map : public Graphics::IDrawable3D, public Graphics::AShadered {
    public:
        Map(std::size_t &width, std::size_t &height);

        bool updateSize(std::size_t x, std::size_t y);
        void updateTile(std::size_t x, std::size_t y,
            const std::vector<std::size_t> &resources);
        void setTilesPosition();

        [[nodiscard]] std::size_t getWidth() const
        {
            return _width;
        }

        void setShader(Graphics::Shader &shader) override;

        [[nodiscard]] std::size_t getHeight() const
        {
            return _height;
        }

        [[nodiscard]] std::map<Info::ResourceName, std::size_t>
        getTotalResources() const
        {
            return _totalResources;
        }

        [[nodiscard]] std::map<Info::ResourceName, std::size_t>
        getTileResources(std::size_t tile) const;

        [[nodiscard]] std::size_t getNextTile(
            InfoBox::Direction dir, std::size_t tile) const;

        void draw3D() const override;

    private:
        void updateTotalResources(
            const std::map<Info::ResourceName, std::size_t> &before,
            std::map<Info::ResourceName, std::size_t> after);

        std::size_t &_width;
        std::size_t &_height;
        std::vector<Tile> _tiles;
        std::map<Info::ResourceName, std::size_t> _totalResources;

        static constexpr auto TILE_WIDTH = 5;
        static constexpr auto TILE_HEIGHT = 5;
        static constexpr auto TILE_Y_POS = 0;

        inline static const std::string TILE_MODEL_PATH =
            Assets::getResource("map/cell.glb");
        raylib::Model _model {TILE_MODEL_PATH};
    };
} // namespace Zappy

#endif /* !MAP_HPP_ */
