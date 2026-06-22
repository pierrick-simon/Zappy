/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Player2D
*/

#ifndef PLAYER2D_HPP_
    #define PLAYER2D_HPP_

    #include <array>
    #include "Info.hpp"
    #include "PlayerStatus.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Sprite2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class Player2D : public Graphics::IDrawable2D {
    public:
        struct PlayerInfo {
            std::size_t id;
            std::string team;
            std::size_t level;
            std::size_t x;
            std::size_t y;
            PlayerStatus::Status status;
            std::map<Info::ResourceName, std::size_t> inventory;
        };

        Player2D(Font &font, std::map<std::string, Color> &teams);

        void update(const PlayerInfo &info);
        void draw2D() const override;

    private:
        void initText(Font &font, raylib::Vector2 pos);
        void initInventory(Font &font, raylib::Vector2 pos);
        void updateInventory(
            const std::map<Info::ResourceName, std::size_t> &inventory);
        void updateTeamName(const std::string &team);

        struct Resource {
            Graphics::Sprite2D sprite;
            Graphics::Text2D text;
        };

        struct TextInfo {
            mutable Graphics::Text2D text;
            std::string prefix;
            std::string value;
            Color color = WHITE;
        };

        enum Text { Team, Level, Position, Status, Inventory, NbText };

        Graphics::Box2D _box;
        Graphics::Text2D _title;
        std::array<TextInfo, NbText> _text;

        Color _teamColor = WHITE;

        std::map<Info::ResourceName, Resource> _resources;

        std::map<std::string, Color> &_teams;
    };
} // namespace Zappy

#endif /* !PLAYER2D_HPP_ */
