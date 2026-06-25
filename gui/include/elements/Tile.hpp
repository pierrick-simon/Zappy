/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Tile
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

    #include <deque>
    #include <map>

    #include "Assets.hpp"
    #include "Info.hpp"
    #include "Resource.hpp"
    #include "graphics/Shader.hpp"
    #include "graphics/primitives/Model.hpp"

namespace Zappy {
    class Tile : public Graphics::Transformable3D {
    public:
        Tile();

        void updateTile(const std::vector<std::size_t> &resources);

        [[nodiscard]] std::map<Info::ResourceName, std::size_t>
        getNbResources() const;

        [[nodiscard]] const std::map<Info::ResourceName, std::deque<Resource>> &
        getResources() const;

        static constexpr raylib::Vector2 TILE_SIZE = {20, 20};

    private:
        std::map<Info::ResourceName, std::deque<Resource>> _resources;

        static void updateResource(std::deque<Resource> &resource,
            std::size_t nb, Info::ResourceName type);
        static const std::map<Info::ResourceName, std::deque<Resource>>
            INIT_RESOURCES;
        static constexpr float TILE_PADDING = 0.3;
        static constexpr float SCALE_MODIF_RANGE = 0.2;
    };
} // namespace Zappy

#endif /* !TILE_HPP_ */
