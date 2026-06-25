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
    TimeUnit::TimeUnit(raylib::Font &font)
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
        for (std::size_t i = 0; i < NBBUTTON; i++) {
            _sprites[i].sprite.Load(PATH[i]);
            _sprites[i].sprite.setColor(Init::GOLD_RICH);
            _sprites[i].sprite.setScale(
                {Init::INFO_BUTTON_SCALE, Init::INFO_BUTTON_SCALE});
            _sprites[i].sprite.setOrigin(
                {Init::INFO_BUTTON_SIZE / 2.f, Init::INFO_BUTTON_SIZE / 2.f});
            if (i <= Action::LEFT)
                _sprites[i].sprite.setRotation(Init::INFO_BUTTON_ROTATION);
        }
        auto left = pos;
        left.x += Init::INFO_SMALL_GAP + Init::INFO_BUTTON_SIZE / 2.f;
        _sprites[FASTLEFT].sprite.setPosition(left);
        left.x += Init::INFO_SMALL_GAP + Init::INFO_BUTTON_SIZE;
        _sprites[LEFT].sprite.setPosition(left);
        auto right = pos;
        right.x += SIZE.x - Init::INFO_SMALL_GAP - Init::INFO_BUTTON_SIZE / 2.f;
        _sprites[FASTRIGHT].sprite.setPosition(right);
        right.x -= Init::INFO_SMALL_GAP + Init::INFO_BUTTON_SIZE;
        _sprites[RIGHT].sprite.setPosition(right);
        _sprites[FASTLEFT].key = KEY_H;
        _sprites[LEFT].key = KEY_J;
        _sprites[RIGHT].key = KEY_L;
        _sprites[FASTRIGHT].key = KEY_SEMICOLON;
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
        for (const auto &[sprite, _] : _sprites)
            sprite.draw2D();
    }

    std::size_t TimeUnit::changeTimeUnit(Action button, std::size_t frequency)
    {
        if (button == FASTLEFT) {
            if (frequency < MOVE_GAP + MIN_FREQUENCY)
                frequency = MIN_FREQUENCY;
            else
                frequency -= MOVE_GAP;
        }
        if (button == LEFT && frequency > MIN_FREQUENCY)
            frequency--;
        if (button == FASTRIGHT) {
            if (frequency > MAX_FREQUENCY - MOVE_GAP)
                frequency = MAX_FREQUENCY;
            else
                frequency += MOVE_GAP;
        }
        if (button == RIGHT && frequency < MAX_FREQUENCY)
            frequency++;
        _button = Action::NONE;
        return std::clamp(frequency, MIN_FREQUENCY, MAX_FREQUENCY);
    }

    void TimeUnit::event(raylib::Camera3D &camera, const raylib::Vector2 &mouse,
        const Ray &ray, bool &leftClick)
    {
        std::size_t i = 0;
        for (auto &[sprite, key] : _sprites) {
            auto pos = sprite.getPosition() - Init::INFO_BUTTON_SIZE / 2.f;
            raylib::Rectangle dest = {
                pos.x, pos.y, Init::INFO_BUTTON_SIZE, Init::INFO_BUTTON_SIZE};
            if (leftClick && dest.CheckCollision(mouse)) {
                _button = static_cast<Action>(i);
                leftClick = false;
                break;
            }
            if (raylib::Keyboard::IsKeyPressed(key)) {
                _button = static_cast<Action>(i);
                break;
            }
            i++;
        }
    }

    const std::array<std::string, TimeUnit::Action::NBBUTTON> TimeUnit::PATH = {
        "public/fastnext.png",
        "public/next.png",
        "public/fastnext.png",
        "public/next.png",
    };
} // namespace Zappy
