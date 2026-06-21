/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Elevation2D
*/

#include "Elevation2D.hpp"
#include "Info.hpp"
#include "Init.hpp"

namespace Zappy {
    Elevation2D::Elevation2D(
        Font &font, std::size_t x, std::size_t y, std::size_t level)
    {
        initText(font, x, y, level);
        initRect();
    }

    void Elevation2D::initText(
        Font &font, std::size_t x, std::size_t y, std::size_t level)
    {
        _titleText.setFont(font);
        _titleText.setStr("Elevation Underway");
        _titleText.setFontSize(TITLE_SIZE);
        _titleText.setColor(Init::GOLD_RICH);
        _levelText.setFont(font);
        _levelText.setFontSize(TEXT_SIZE);
        _levelText.setColor(WHITE);
        _levelText.setStr("Level : " + std::to_string(level));
        _posText.setFont(font);
        _posText.setFontSize(TEXT_SIZE);
        _posText.setColor(WHITE);
        _posText.setStr(
            "Position : (" + std::to_string(x) + "," + std::to_string(y) + ")");
    }

    void Elevation2D::initRect()
    {
        _box.setSize(Init::INCANTATION_SIZE);
        _box.setBorderSize(Init::BORDER_SIZE);
        _box.setRound(Init::BORDER_ROUND);
        _box.setBorderColor(Init::GOLD_RICH);
        _box.setColor(Init::DARK_PINEWOOD);
        _status.setRound(Init::BORDER_SIZE);
        _status.setColor(Init::GOLD_RICH);
    }

    void Elevation2D::setPos(Vector2 pos)
    {
        _box.setPos(pos);
        pos.x += Init::INCANTATION_GAP;
        pos.y += Init::INCANTATION_GAP;
        _titleText.setPosition(pos);
        pos.y += TITLE_SIZE + SMALL_GAP;
        _levelText.setPosition(pos);
        pos.y += TEXT_SIZE + SMALL_GAP;
        _posText.setPosition(pos);
        pos.y += TEXT_SIZE + Init::INCANTATION_GAP;
        _status.setPos(pos);
    }

    void Elevation2D::update(float dt)
    {
        _timer += dt;
        _timer = std::min(_timer, TIME);
        _status.setSize({_timer / TIME *
                (Init::INCANTATION_SIZE.x - Init::INCANTATION_GAP * 2.f),
            SATUS_HEGHT});
    }

    void Elevation2D::draw2D() const
    {
        _box.draw2D();
        _status.draw2D();
        _titleText.draw2D();
        _levelText.draw2D();
        _posText.draw2D();
    }
} // namespace Zappy
