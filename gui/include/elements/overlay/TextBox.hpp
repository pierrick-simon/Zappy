/*
** EPITECH PROJECT, 2026
** gui
** File description:
** TextBox
*/

#ifndef TEXTBOX_HPP_
    #define TEXTBOX_HPP_

    #include <map>
    #include <vector>
    #include "Init.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class TextBox : public Graphics::IDrawable2D {
    public:
        TextBox(raylib::Font &font, std::map<std::string, raylib::Color> &teams,
            raylib::Color boxColor);

        void setWidth(float width);
        void setPos(Vector2 pos);
        void setMaxLine(std::size_t maxLine);
        void setFontSize(float fontSize);
        void setTextColor(raylib::Color color);

        [[nodiscard]] float getHeight() const;

        void addMessage(
            const std::string &team, std::size_t id, std::string msg);

        void draw2D() const override;

    private:
        void handleSeparator(char c, std::string &word, std::string &line,
            std::vector<std::string> &lines, float maxWidth);
        void handleChar(char c, std::string &word, std::string &line,
            std::vector<std::string> &lines, float maxWidth);
        void pushWord(std::string &word, std::string &line,
            std::vector<std::string> &lines, float maxWidth);
        std::vector<std::string> wrapText(
            const std::string &text, float maxWidth);
        void pushPrefix(const std::string &team, std::size_t id,
            std::string &msg, float maxWidth);

        struct Line {
            std::string teamPrefix;
            std::string body;
            raylib::Color teamColor;
        };

        std::vector<Line> _lines;
        mutable Graphics::Text2D _text;
        Graphics::Box2D _box;
        std::size_t _maxLine = 0;
        float _fontSize = 0.f;
        raylib::Vector2 _pos = {0, 0};
        raylib::Vector2 _size = {0, 0};
        raylib::Vector2 _origin = {0, 0};
        raylib::Color _color = raylib::Color::White();

        std::map<std::string, raylib::Color> &_teams;
    };
} // namespace Zappy

#endif /* !TEXTBOX_HPP_ */
