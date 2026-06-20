/*
** EPITECH PROJECT, 2026
** gui
** File description:
** ChatBox
*/

#include "ChatBox.hpp"
#include "Init.hpp"

namespace Zappy {
    ChatBox::ChatBox(
        Font &font, std::unordered_map<std::string, Color> &teams) :
        _teams(teams)
    {

        auto x = float(GetScreenWidth());
        auto y = float(GetScreenHeight());
        _text.setSpacing(Init::LETTER_SPACING);
        _text.setFontSize(FONT_SIZE);
        _text.setPosition({x - TEXT_POS.x, y - TEXT_POS.y});
        _text.setFont(font);
        _text.setColor(WHITE);
        _box.setSize(BOX_SIZE);
        _box.setPos({x - BOX_POS.x, y - BOX_POS.y});
        _box.setRound(Init::BORDER_ROUND);
        _box.setColor(Init::BLUE_THROUGH);
    }

    void ChatBox::pushWord(std::string &word, std::string &line,
        std::vector<std::string> &lines, float maxWidth)
    {
        if (word.empty())
            return;

        std::string test = line.empty() ? word : line + " " + word;
        _text.setStr(test);
        Vector2 testSize = _text.getSize();
        if (!line.empty() && testSize.x > maxWidth) {
            lines.push_back(line);
            line = word;
        } else {
            line = test;
        }
        word.clear();
    }

    void ChatBox::handleSeparator(char c, std::string &word, std::string &line,
        std::vector<std::string> &lines, float maxWidth)
    {
        pushWord(word, line, lines, maxWidth);
        if (c == '\n') {
            lines.push_back(line);
            line.clear();
        }
    }

    void ChatBox::handleChar(char c, std::string &word, std::string &line,
        std::vector<std::string> &lines, float maxWidth)
    {
        word += c;
        _text.setStr(word);
        Vector2 wordSize = _text.getSize();
        if (wordSize.x > maxWidth) {
            if (!line.empty()) {
                lines.push_back(line);
                line.clear();
            }
            std::string partial = word.substr(0, word.size() - 1);
            lines.push_back(partial);
            word = std::string(1, c);
        }
    }

    std::vector<std::string> ChatBox::wrapText(
        const std::string &text, float maxWidth)
    {
        std::vector<std::string> lines;
        std::string currentLine;
        std::string currentWord;

        for (auto c : text) {
            if (c == ' ' || c == '\n')
                handleSeparator(c, currentWord, currentLine, lines, maxWidth);
            else
                handleChar(c, currentWord, currentLine, lines, maxWidth);
        }
        pushWord(currentWord, currentLine, lines, maxWidth);
        if (!currentLine.empty())
            lines.push_back(currentLine);
        return lines;
    }

    void ChatBox::pushPrefix(const std::string &team, std::size_t id,
        std::string &msg, float maxWidth)
    {
        std::string prefixMsg = team + "[" + std::to_string(id) + "]:";
        auto prefix = wrapText(prefixMsg, maxWidth);
        if (prefixMsg.empty())
            return;
        auto color = WHITE;
        auto it = _teams.find(team);
        if (it != _teams.end())
            color = it->second;
        for (std::size_t i = 0; i < prefix.size() - 1; i++) {
            if (_lines.size() >= MAX_LINE)
                _lines.erase(_lines.begin());
            _lines.push_back({prefix[i], "", color});
        }
        _text.setStr(*prefix.rbegin() + " ");
        float prefixWidth = _text.getSize().x;
        auto firstLines = wrapText(msg, maxWidth - prefixWidth);
        std::string firstBody;
        if (!firstLines.empty())
            firstBody = firstLines[0];
        msg = msg.substr(firstBody.size());
        if (_lines.size() >= MAX_LINE)
            _lines.erase(_lines.begin());
        _lines.push_back({*prefix.rbegin() + " ", firstBody, color});
    }

    void ChatBox::addMessage(
        const std::string &team, std::size_t id, std::string msg)
    {
        float boxInnerWidth = BOX_SIZE.x - 2 * GAP;

        pushPrefix(team, id, msg, boxInnerWidth);
        auto restLines = wrapText(msg, boxInnerWidth);
        for (const auto &body : restLines) {
            if (_lines.size() >= MAX_LINE)
                _lines.erase(_lines.begin());
            _lines.push_back({"", body, WHITE});
        }
    }

    void ChatBox::draw2D() const
    {
        _box.draw2D();
        float startX = float(GetScreenWidth()) - TEXT_POS.x;
        float y = float(GetScreenHeight()) - TEXT_POS.y;
        if (_lines.size() < MAX_LINE)
            y += float(MAX_LINE - _lines.size()) * FONT_SIZE;
        for (const auto &line : _lines) {
            float x = startX;
            _text.setPosition({x, y});
            _text.setColor(line.teamColor);
            _text.setStr(line.teamPrefix);
            _text.draw2D();
            _text.setStr(line.teamPrefix);
            Vector2 prefixSize = _text.getSize();
            x += prefixSize.x;
            _text.setStr(line.body);
            _text.setPosition({x, y});
            _text.setColor(WHITE);
            _text.draw2D();
            y += FONT_SIZE;
        }
    }
} // namespace Zappy
