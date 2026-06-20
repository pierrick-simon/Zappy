/*
** EPITECH PROJECT, 2026
** gui
** File description:
** ChatBox
*/

#ifndef CHATBOX_HPP_
    #define CHATBOX_HPP_

    #include <unordered_map>
    #include <vector>
    #include "Init.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class ChatBox : public Graphics::IDrawable2D {
    public:
        ChatBox(Font &font, std::unordered_map<std::string, Color> &teams);

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

        std::unordered_map<std::string, Color> &_teams;

        static constexpr std::size_t MAX_LINE = 15;
        static constexpr float FONT_SIZE = 30;
        static constexpr float GAP = 10.f;
        static constexpr Vector2 BOX_SIZE = {
            300, GAP * 2.f + MAX_LINE *FONT_SIZE};
        static constexpr Vector2 BOX_POS = {BOX_SIZE.x + GAP, BOX_SIZE.y + GAP};
        static constexpr Vector2 TEXT_POS = {BOX_POS.x - GAP, BOX_POS.y - GAP};
    };
} // namespace Zappy

#endif /* !CHATBOX_HPP_ */
