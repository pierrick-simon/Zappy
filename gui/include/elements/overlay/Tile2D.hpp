/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Tile2D
*/

#ifndef TILE2D_HPP_
    #define TILE2D_HPP_

    #include <array>
    #include "Info.hpp"
    #include "InfoBox.hpp"
    #include "Init.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Sprite2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class Tile2D : public InfoBox, public Graphics::IDrawable2D {
    public:
        struct TileInfo {
            std::size_t x;
            std::size_t y;
            std::size_t nbPlayer;
            std::size_t nbEgg;
            std::size_t nbElevation;
            std::map<Info::ResourceName, std::size_t> resources;
        };

        Tile2D(raylib::Font &font);

        Action update(const TileInfo &info);
        void draw2D() const override;
        void changeSelected(Action dir) override;

    private:
        void initText(raylib::Font &font, raylib::Vector2 pos);
        void initResources(raylib::Font &font, raylib::Vector2 pos);
        void updateResources(
            const std::map<Info::ResourceName, std::size_t> &resources);

        struct Resource {
            Graphics::Sprite2D sprite;
            Graphics::Text2D text;
        };

        struct TextInfo {
            mutable Graphics::Text2D text;
            std::string prefix;
            std::string value;
            raylib::Color color = raylib::Color::White();
        };

        enum Text { NBPLAYER, NBEGG, NBELVATION, RESOURCES, NBTEXT };

        Graphics::Text2D _title;
        std::array<TextInfo, NBTEXT> _text;

        raylib::Color _teamColor = raylib::Color::White();

        std::map<Info::ResourceName, Resource> _resources;

        Action _dir = Action::NONE;

        static constexpr std::size_t ELEVATION_MAX = Init::INFO_MAX / 100;
    };
} // namespace Zappy

#endif /* !TILE2D_HPP_ */
