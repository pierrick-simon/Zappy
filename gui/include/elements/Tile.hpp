/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Tile
*/

#ifndef TILE_HPP_
    #define TILE_HPP_

    #include <map>
    #include <queue>

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

    private:
        std::map<Info::ResourceName, std::queue<Resource>> _resources;

        static void updateResource(std::queue<Resource> &resource,
            std::size_t nb, Info::ResourceName type);
        static const std::map<Info::ResourceName, std::queue<Resource>>
            INIT_RESOURCES;
    };
} // namespace Zappy

#endif /* !TILE_HPP_ */
