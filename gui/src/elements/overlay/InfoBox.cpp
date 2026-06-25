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
        _buttons.emplace(Action::LEFT, Button {Graphics::Sprite2D(), KEY_LEFT});
        _buttons.emplace(
            Action::RIGHT, Button {Graphics::Sprite2D(), KEY_RIGHT});
        if (_close) {
            _buttons.emplace(
                Action::CLOSE, Button {Graphics::Sprite2D(), KEY_BACKSPACE});
            _buttons[Action::CLOSE].sprite.setPosition(
                {pos.x + Init::INFO_SIZE_X - Init::GAP -
                        Init::INFO_BUTTON_SIZE / 2.f,
                    pos.y - Init::INFO_SMALL_GAP});
        }
        pos.y += Init::GAP + Init::INFO_TITLE_SIZE / 2.f;
        initSpriteInfo(pos);
        _buttons[Action::LEFT].sprite.setRotation(Init::INFO_BUTTON_ROTATION);
        _buttons[Action::LEFT].sprite.setPosition(
            {pos.x + Init::GAP + Init::INFO_BUTTON_SIZE / 2.f, pos.y});
        _buttons[Action::RIGHT].sprite.setPosition({pos.x + Init::INFO_SIZE_X -
                Init::GAP - Init::INFO_BUTTON_SIZE / 2.f,
            pos.y});
    }

    void InfoBox::initSpriteInfo(raylib::Vector2 pos)
    {
        for (auto &[name, button] : _buttons) {
            if (name == Action::CLOSE) {
                button.sprite.Load(IMG_CLOSE.data());
                button.sprite.setScale({CLOSE_SCALE, CLOSE_SCALE});
                button.sprite.setColor(raylib::Color::Red());
            } else {
                button.sprite.Load(Init::IMG_NEXT.data());
                button.sprite.setScale(
                    {Init::INFO_BUTTON_SCALE, Init::INFO_BUTTON_SCALE});
                button.sprite.setColor(Init::GOLD_RICH);
            }
            button.sprite.setOrigin(
                {Init::INFO_BUTTON_SIZE / 2.f, Init::INFO_BUTTON_SIZE / 2.f});
        }
    }

    void InfoBox::event(raylib::Camera3D &camera, const raylib::Vector2 &mouse,
        const Ray &ray, bool &leftClick)
    {
        for (auto &[name, button] : _buttons) {
            auto pos =
                button.sprite.getPosition() - Init::INFO_BUTTON_SIZE / 2.f;
            raylib::Rectangle dest = {
                pos.x, pos.y, Init::INFO_BUTTON_SIZE, Init::INFO_BUTTON_SIZE};
            if (leftClick && dest.CheckCollision(mouse)) {
                changeSelected(name);
                leftClick = false;
                break;
            }
            if (raylib::Keyboard::IsKeyPressed(button.key)) {
                changeSelected(name);
                break;
            }
        }
    }
} // namespace Zappy
