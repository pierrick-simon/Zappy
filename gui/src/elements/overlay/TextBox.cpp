/*
** EPITECH PROJECT, 2026
** gui
** File description:
** TextBox
*/

#include "TextBox.hpp"
#include "Init.hpp"

namespace Zappy {

    TextBox::TextBox(Font &font, std::unordered_map<std::string, Color> &teams,
        Color boxColor) :
        _teams(teams)
    {
        _text.setSpacing(Init::LETTER_SPACING);
        _text.setFont(font);
        _text.setColor(_color);
        _text.setFontSize(_fontSize);
        _box.setSize(_size);
        _box.setPos(_pos);
        _box.setRound(Init::BORDER_ROUND);
        _box.setColor(boxColor);
    }

    void TextBox::setWidth(float width)
    {
        _size.x = width;
        _box.setSize(_size);
    }

    void TextBox::setPos(Vector2 pos)
    {
        _pos = pos;
        _box.setPos(_pos);
    }

    void TextBox::setMaxLine(std::size_t maxLine)
    {
        _maxLine = maxLine;
        _size.y = Init::GAP * 2.f + float(_maxLine) * _fontSize;
        _box.setSize(_size);
    }

    void TextBox::setFontSize(float fontSize)
    {
        _fontSize = fontSize;
        _size.y = Init::GAP * 2.f + float(_maxLine) * _fontSize;
        _box.setSize(_size);
        _text.setFontSize(fontSize);
    }

    void TextBox::setTextColor(Color color)
    {
        _color = color;
    }

    float TextBox::getHeight() const
    {
        return _size.y;
    }

    void TextBox::pushWord(std::string &word, std::string &line,
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

    void TextBox::handleSeparator(char c, std::string &word, std::string &line,
        std::vector<std::string> &lines, float maxWidth)
    {
        pushWord(word, line, lines, maxWidth);
        if (c == '\n') {
            lines.push_back(line);
            line.clear();
        }
    }

    void TextBox::handleChar(char c, std::string &word, std::string &line,
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

    std::vector<std::string> TextBox::wrapText(
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

    void TextBox::pushPrefix(const std::string &team, std::size_t id,
        std::string &msg, float maxWidth)
    {
        std::string prefixMsg = team + "[" + std::to_string(id) + "]:";
        auto prefix = wrapText(prefixMsg, maxWidth);
        if (prefixMsg.empty())
            return;
        auto color = _color;
        auto it = _teams.find(team);
        if (it != _teams.end())
            color = it->second;
        for (std::size_t i = 0; i < prefix.size() - 1; i++) {
            if (_lines.size() >= _maxLine)
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
        if (_lines.size() >= _maxLine)
            _lines.erase(_lines.begin());
        _lines.push_back({*prefix.rbegin() + " ", firstBody, color});
    }

    void TextBox::addMessage(
        const std::string &team, std::size_t id, std::string msg)
    {
        float boxInnerWidth = _size.x - 2 * Init::GAP;

        pushPrefix(team, id, msg, boxInnerWidth);
        auto restLines = wrapText(msg, boxInnerWidth);
        for (const auto &body : restLines) {
            if (_lines.size() >= _maxLine)
                _lines.erase(_lines.begin());
            _lines.push_back({"", body, _color});
        }
    }

    void TextBox::draw2D() const
    {
        _box.draw2D();
        float startX = _pos.x + Init::GAP;
        float y = _pos.y + Init::GAP;
        if (_lines.size() < _maxLine)
            y += float(_maxLine - _lines.size()) * _fontSize;
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
            _text.setColor(_color);
            _text.draw2D();
            y += _fontSize;
        }
    }
} // namespace Zappy
