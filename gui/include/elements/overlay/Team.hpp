/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Team
*/

#ifndef TEAM_HPP_
    #define TEAM_HPP_

    #include <array>
    #include <map>
    #include <optional>
    #include <string_view>
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Sprite2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class Team : public Graphics::IDrawable2D {
    public:
        static constexpr std::size_t NB_LEVEL = 8;

        struct TeamInfo {
            std::size_t nbEgg;
            std::array<std::size_t, NB_LEVEL> level;
        };

        Team(Font &font, std::map<std::string, Color> &teams);
        void update(const TeamInfo &info);
        void draw2D() const override;

        void setSelectTeam(const std::string &team);
        [[nodiscard]] std::optional<std::string> getSelectTeam()
        {
            return _selectTeam;
        }

    private:
        void initText(Font &font, raylib::Vector2 pos);
        void initSprite(raylib::Vector2 pos);
        void updateTitle(const std::string &team);
        void updateMembers(const std::array<std::size_t, NB_LEVEL> &levels);
        void changeSelectTeam(int value);

        enum Text { NbPlayer, NbEgg, Level, NbText };

        struct TextInfo {
            mutable Graphics::Text2D text;
            std::string prefix;
            std::string value;
        };

        Graphics::Box2D _box;
        Graphics::Text2D _title;
        std::array<TextInfo, NbText> _text;
        std::array<TextInfo, NB_LEVEL> _levels;
        Graphics::Sprite2D _prevButton;
        Graphics::Sprite2D _nextButton;

        std::optional<std::string> _selectTeam;

        std::map<std::string, Color> &_teams;

        static constexpr float SIZE_X = 250;

        static constexpr float BUTTON_SIZE = 25;
        static constexpr float BUTTON_ROTATION = 180;
        static constexpr float IMG_SIZE = 166;
        static constexpr float BUTTON_SCALE = BUTTON_SIZE / IMG_SIZE;
        static constexpr std::string_view IMG_PATH = "public/next.png";
    };
} // namespace Zappy

#endif /* !TEAM_HPP_ */
