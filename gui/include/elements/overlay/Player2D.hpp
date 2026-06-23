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
    #include "InfoBox.hpp"
    #include "PlayerStatus.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Sprite2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class Player2D : public InfoBox, public Graphics::IDrawable2D {
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

        Player2D(
            raylib::Font &font, std::map<std::string, raylib::Color> &teams);

        Action update(const PlayerInfo &info);
        void draw2D() const override;
        void changeSelected(Action dir) override;

    private:
        void initText(raylib::Font &font, raylib::Vector2 pos);
        void initInventory(raylib::Font &font, raylib::Vector2 pos);
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
            raylib::Color color = raylib::Color::White();
        };

        enum Text { TEAM, LEVEL, POSITION, STATUS, INVENTORY, NBTEXT };

        Graphics::Text2D _title;
        std::array<TextInfo, NBTEXT> _text;

        raylib::Color _teamColor = raylib::Color::White();

        std::map<Info::ResourceName, Resource> _resources;

        std::map<std::string, raylib::Color> &_teams;

        Action _dir = Action::NONE;
    };
} // namespace Zappy

#endif /* !PLAYER2D_HPP_ */
