/*
** EPITECH PROJECT, 2026
** gui
** File description:
** ResourceInfo
*/

#ifndef RESOURCEINFO_HPP_
    #define RESOURCEINFO_HPP_

    #include "Init.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Sprite2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class ResourceInfo : public Graphics::IDrawable2D {
    public:
        struct TextureSize {
            std::string path;
            raylib::Vector2 size;
        };

        ResourceInfo(raylib::Font &font, const raylib::Vector2 &pos,
            const TextureSize &texture);

        void draw2D() const override;
        void update(std::size_t map, std::size_t players);

    private:
        void initSprite(const TextureSize &texture);
        void initText(raylib::Font &font);
        void initRect();

        raylib::Vector2 _pos;
        Graphics::Text2D _text;
        Graphics::Box2D _rec;

        Graphics::Text2D _map;
        Graphics::Text2D _player;
        Graphics::Box2D _info;

        Graphics::Sprite2D _resourceIcon;
        Graphics::Sprite2D _houseIcon;
        Graphics::Sprite2D _golemIcon;

        static constexpr std::size_t MAX = 999999;
        static constexpr float FONTSIZE = 25;
        static constexpr std::string_view HOUSE_ICON = "public/houseIcon.png";
        static constexpr raylib::Vector2 HOUSE_ICON_SIZE = {500, 400};
        static constexpr float HOUSE_RATIO =
            Init::RESOURCE_ICON / HOUSE_ICON_SIZE.y;
        static const inline raylib::Vector2 HOUSE_ICON_ORIGIN =
            HOUSE_ICON_SIZE * HOUSE_RATIO / 2.0f;
        static constexpr std::string_view GOLEM_ICON = "public/golemIcon.png";
        static constexpr raylib::Vector2 GOLEM_ICON_SIZE = {700, 500};
        static constexpr float GOLEM_RATIO =
            Init::RESOURCE_ICON / GOLEM_ICON_SIZE.y;
        static const inline raylib::Vector2 GOLEM_ICON_ORIGIN =
            GOLEM_ICON_SIZE * GOLEM_RATIO / 2.0f;
    };
} // namespace Zappy

#endif /* !RESOURCEINFO_HPP_ */
