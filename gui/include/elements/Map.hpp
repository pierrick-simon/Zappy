/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Map
*/

#ifndef MAP_HPP_
    #define MAP_HPP_

    #include <numeric>
#include <optional>
    #include <unordered_map>
    #include "Info.hpp"
    #include "InfoBox.hpp"
    #include "Tile.hpp"
    #include "graphics/AShadered.hpp"
    #include "graphics/IDrawable3D.hpp"
    #include "graphics/IEvent.hpp"

namespace Zappy {
    class Map : public Graphics::IDrawable3D,
                public Graphics::AShadered,
                public Graphics::IUpdatable,
                public Graphics::IEvent {
    public:
        Map(std::size_t &width, std::size_t &height,
            std::optional<std::size_t> &selectPlayer,
            std::optional<std::size_t> &selectTile);

        bool updateSize(std::size_t x, std::size_t y);
        void updateTile(std::size_t x, std::size_t y,
            const std::vector<std::size_t> &resources);
        void setTilesPosition();

        [[nodiscard]] raylib::Vector2 getTilePosition(size_t x, size_t y) const;

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
            InfoBox::Action dir, std::size_t tile) const;

        void drawRessources(const Zappy::Tile &tile) const;
        void drawGrass() const;
        void draw3D() const override;
        void update(float dt) override;
        void event(raylib::Camera3D &camera, const raylib::Vector2 &mouse,
            const Ray &ray, bool &leftClick) override;

    private:
        void updateTotalResources(
            const std::map<Info::ResourceName, std::size_t> &before,
            std::map<Info::ResourceName, std::size_t> after);
        void spawnGrass();

        std::size_t &_width;
        std::size_t &_height;
        raylib::Vector2 _renderedMapSize;
        std::vector<Tile> _tiles;
        std::map<Info::ResourceName, std::size_t> _totalResources;
        std::unordered_map<Info::ResourceName, raylib::Model>
            _ressources_models;

        static constexpr std::size_t NB_GRASS_MODELS = 4;
        std::array<raylib::Model, NB_GRASS_MODELS> _grassModels;
        static constexpr float GRASS_DENSITY = 0.05f;
        static constexpr auto GRASS_PER_TILE = static_cast<std::size_t>(
            GRASS_DENSITY * Tile::TILE_SIZE.x * Tile::TILE_SIZE.y);
        static constexpr float MAX_GRASS_SCALE = 0.25f;
        static constexpr float MIN_GRASS_SCALE = 0.15f;
        static constexpr float BORDER_GRASS = 1.f;
        std::vector<std::pair<std::size_t, Graphics::Transformable3D>> _grasses;

        bool _changeColor = false;
        float _blink = 0.f;
        std::optional<std::size_t> &_selectPlayer;
        std::optional<std::size_t> &_selectTile;

        static constexpr auto TILE_Y_POS = 0;
        static constexpr raylib::Vector2 GROUND_SIZE = {5, 5};
        static constexpr auto TILE_SCALE_MARGIN = 0.02f;
        static constexpr raylib::Vector3 TILE_SCALE = {
            Tile::TILE_SIZE.x / GROUND_SIZE.x + TILE_SCALE_MARGIN,
            std::midpoint(Tile::TILE_SIZE.x / GROUND_SIZE.x,
                Tile::TILE_SIZE.y / GROUND_SIZE.y),
            Tile::TILE_SIZE.y / GROUND_SIZE.y + TILE_SCALE_MARGIN};

        inline static const std::string TILE_MODEL_PATH =
            Assets::getResource("map/cell.glb");
        raylib::Model _tileModel {TILE_MODEL_PATH};

        static constexpr auto DEFAULT_MATERIAL = 1;
        static constexpr auto GRASS_MATERIAL = 1;
        static constexpr auto DIRT_MATERIAL = 2;

        static const std::unordered_map<Info::ResourceName, float> _modelScales;
    };
} // namespace Zappy

#endif /* !MAP_HPP_ */
