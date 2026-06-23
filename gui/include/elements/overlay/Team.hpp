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
    #include "InfoBox.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class Team : public InfoBox, public Graphics::IDrawable2D {
    public:
        static constexpr std::size_t NB_LEVEL = 8;

        struct TeamInfo {
            std::size_t nbEgg;
            std::array<std::size_t, NB_LEVEL> level;
        };

        Team(raylib::Font &font, std::map<std::string, raylib::Color> &teams);
        void update(const TeamInfo &info);
        void draw2D() const override;
        void changeSelected(Action dir) override;

        void setSelectTeam(const std::string &team);
        [[nodiscard]] std::optional<std::string> getSelectTeam()
        {
            return _selectTeam;
        }

    private:
        void initText(raylib::Font &font, raylib::Vector2 pos);
        void updateTitle(const std::string &team);
        void updateMembers(const std::array<std::size_t, NB_LEVEL> &levels);

        enum Text { NBPLAYER, NBEGG, LEVEL, NBTEXT };

        struct TextInfo {
            mutable Graphics::Text2D text;
            std::string prefix;
            std::string value;
        };

        Graphics::Text2D _title;
        std::array<TextInfo, NBTEXT> _text;
        std::array<TextInfo, NB_LEVEL> _levels;

        std::optional<std::string> _selectTeam;

        std::map<std::string, raylib::Color> &_teams;
    };
} // namespace Zappy

#endif /* !TEAM_HPP_ */
