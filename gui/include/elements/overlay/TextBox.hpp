/*
** EPITECH PROJECT, 2026
** gui
** File description:
** TextBox
*/

#ifndef TEXTBOX_HPP_
    #define TEXTBOX_HPP_

    #include <unordered_map>
    #include <vector>
    #include "Init.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class TextBox : public Graphics::IDrawable2D {
    public:
        TextBox(Font &font, std::unordered_map<std::string, Color> &teams,
            Color boxColor);

        void setWidth(float width);
        void setPos(Vector2 pos);
        void setMaxLine(std::size_t maxLine);
        void setFontSize(float fontSize);
        void setTextColor(Color color);

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
            Color teamColor;
        };

        std::vector<Line> _lines;
        mutable Graphics::Text2D _text;
        Graphics::Box2D _box;
        std::size_t _maxLine = 0;
        float _fontSize = 0.f;
        Vector2 _pos = {0, 0};
        Vector2 _size = {0, 0};
        Vector2 _origin = {0, 0};
        Color _color = WHITE;

        std::unordered_map<std::string, Color> &_teams;
    };
} // namespace Zappy

#endif /* !TEXTBOX_HPP_ */
