/*
** EPITECH PROJECT, 2026
** gui
** File description:
** InfoBox
*/

#include "InfoBox.hpp"
#include "Init.hpp"

namespace Zappy {
    InfoBox::InfoBox(raylib::Vector2 pos, bool close) :
        _close(close)
    {
        initSprite(pos);
        if (close)
            pos.y -= Init::INFO_BUTTON_SIZE + Init::INFO_SMALL_GAP;
        _box.setPos(pos);
        _box.setBorderSize(Init::BORDER_SIZE);
        _box.setRound(Init::BORDER_ROUND);
        _box.setBorderColor(Init::GOLD_RICH);
        _box.setColor(Init::DARK_PINEWOOD);
    }

    void InfoBox::setSize(raylib::Vector2 size)
    {
        if (_close)
            size.y += Init::INFO_BUTTON_SIZE + Init::INFO_SMALL_GAP;
        _box.setSize(size);
    }

    void InfoBox::initSprite(raylib::Vector2 pos)
    {
        _buttons.emplace(Action::Left, Graphics::Sprite2D());
        _buttons.emplace(Action::Right, Graphics::Sprite2D());
        if (_close) {
            _buttons.emplace(Action::Close, Graphics::Sprite2D());
            _buttons[Action::Close].setPosition({pos.x + Init::INFO_SIZE_X -
                    Init::GAP - Init::INFO_BUTTON_SIZE / 2.f,
                pos.y - Init::INFO_SMALL_GAP});
        }
        pos.y += Init::GAP + Init::INFO_TITLE_SIZE / 2.f;
        initSpriteInfo(pos);
        _buttons[Action::Left].setRotation(Init::INFO_BUTTON_ROTATION);
        _buttons[Action::Left].setPosition(
            {pos.x + Init::GAP + Init::INFO_BUTTON_SIZE / 2.f, pos.y});
        _buttons[Action::Right].setPosition({pos.x + Init::INFO_SIZE_X -
                Init::GAP - Init::INFO_BUTTON_SIZE / 2.f,
            pos.y});
    }

    void InfoBox::initSpriteInfo(raylib::Vector2 pos)
    {
        for (auto &[name, button] : _buttons) {
            if (name == Action::Close) {
                button.Load(IMG_CLOSE.data());
                button.setScale({CLOSE_SCALE, CLOSE_SCALE});
                button.setColor(raylib::Color::Red());
            } else {
                button.Load(Init::IMG_NEXT.data());
                button.setScale(
                    {Init::INFO_BUTTON_SCALE, Init::INFO_BUTTON_SCALE});
                button.setColor(Init::GOLD_RICH);
            }
            button.setOrigin(
                {Init::INFO_BUTTON_SIZE / 2.f, Init::INFO_BUTTON_SIZE / 2.f});
        }
    }
} // namespace Zappy
