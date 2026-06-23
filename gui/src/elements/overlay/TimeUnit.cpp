/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** TimeUnit
*/

#include "TimeUnit.hpp"
#include <algorithm>
#include "Init.hpp"

namespace Zappy {
    TimeUnit::TimeUnit(Font &font)
    {
        auto x = float(Init::WINDOW_SIZE_X) - Init::GAP - SIZE.x;
        raylib::Vector2 pos(x, Init::GAP);
        _text.setFont(font);
        _text.setColor(Init::GOLD_RICH);
        _text.setFontSize(TEXT_SIZE);
        _text.setPosition({pos.x + SIZE.x / 2.f, pos.y + SIZE.y / 2.f});
        _box.setSize(SIZE);
        _box.setPos(pos);
        _box.setBorderSize(Init::BORDER_SIZE);
        _box.setRound(Init::BORDER_ROUND);
        _box.setBorderColor(Init::GOLD_RICH);
        _box.setColor(Init::DARK_PINEWOOD);
        initSprite(pos);
    }

    void TimeUnit::initSprite(raylib::Vector2 pos)
    {
        pos.y += SIZE.y / 2.f;
        for (std::size_t i = 0; i < NbButton; i++) {
            _sprites[i].Load(PATH[i]);
            _sprites[i].setColor(Init::GOLD_RICH);
            _sprites[i].setScale(
                {Init::INFO_BUTTON_SCALE, Init::INFO_BUTTON_SCALE});
            _sprites[i].setOrigin(
                {Init::INFO_BUTTON_SIZE / 2.f, Init::INFO_BUTTON_SIZE / 2.f});
            if (i <= Button::Left)
                _sprites[i].setRotation(Init::INFO_BUTTON_ROTATION);
        }
        auto left = pos;
        left.x += Init::INFO_SMALL_GAP + Init::INFO_BUTTON_SIZE / 2.f;
        _sprites[FastLeft].setPosition(left);
        left.x += Init::INFO_SMALL_GAP + Init::INFO_BUTTON_SIZE;
        _sprites[Left].setPosition(left);
        auto right = pos;
        right.x += SIZE.x - Init::INFO_SMALL_GAP - Init::INFO_BUTTON_SIZE / 2.f;
        _sprites[FastRight].setPosition(right);
        right.x -= Init::INFO_SMALL_GAP + Init::INFO_BUTTON_SIZE;
        _sprites[Right].setPosition(right);
    }

    std::size_t TimeUnit::update(std::size_t timeUnit)
    {
        _text.setStr("x" + std::to_string(timeUnit));
        auto tmp = _text.getSize();
        _text.setOrigin(tmp / 2.f);
        return changeTimeUnit(_button, timeUnit);
    }

    void TimeUnit::draw2D() const
    {
        _box.draw2D();
        _text.draw2D();
        for (const auto &sprite : _sprites)
            sprite.draw2D();
    }

    std::size_t TimeUnit::changeTimeUnit(Button button, std::size_t frequency)
    {
        if (button == FastLeft) {
            if (frequency < MOVE_GAP + MIN_FREQUENCY)
                frequency = MIN_FREQUENCY;
            else
                frequency -= MOVE_GAP;
        }
        if (button == Left && frequency > MIN_FREQUENCY)
            frequency--;
        if (button == FastRight) {
            if (frequency > MAX_FREQUENCY - MOVE_GAP)
                frequency = MAX_FREQUENCY;
            else
                frequency += MOVE_GAP;
        }
        if (button == Right && frequency < MAX_FREQUENCY)
            frequency++;
        _button = Button::None;
        return std::clamp(frequency, MIN_FREQUENCY, MAX_FREQUENCY);
    }

    const std::array<std::string, TimeUnit::Button::NbButton> TimeUnit::PATH = {
        "public/fastnext.png",
        "public/next.png",
        "public/fastnext.png",
        "public/next.png",
    };
} // namespace Zappy
