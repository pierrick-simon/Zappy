/*
** EPITECH PROJECT, 2026
** gui
** File description:
** InfoBox
*/

#include "InfoBox.hpp"
#include "Init.hpp"

namespace Zappy {
    InfoBox::InfoBox(raylib::Vector2 pos)
    {
        initSprite(pos);
        _box.setPos(pos);
        _box.setBorderSize(Init::BORDER_SIZE);
        _box.setRound(Init::BORDER_ROUND);
        _box.setBorderColor(Init::GOLD_RICH);
        _box.setColor(Init::DARK_PINEWOOD);
    }

    void InfoBox::setSize(raylib::Vector2 size)
    {
        _box.setSize(size);
    }

    void InfoBox::initSprite(raylib::Vector2 pos)
    {
        pos.y += Init::GAP + Init::INFO_TITLE_SIZE / 2.f;
        _prevButton.Load(Init::IMG_NEXT.data());
        _prevButton.setScale(
            {Init::INFO_BUTTON_SCALE, Init::INFO_BUTTON_SCALE});
        _prevButton.setOrigin(
            {Init::INFO_BUTTON_SIZE / 2.f, Init::INFO_BUTTON_SIZE / 2.f});
        _prevButton.setRotation(Init::INFO_BUTTON_ROTATION);
        _prevButton.setColor(Init::GOLD_RICH);
        _prevButton.setPosition(
            {pos.x + Init::GAP + Init::INFO_BUTTON_SIZE / 2.f, pos.y});
        _nextButton.Load(Init::IMG_NEXT.data());
        _nextButton.setScale(
            {Init::INFO_BUTTON_SCALE, Init::INFO_BUTTON_SCALE});
        _nextButton.setOrigin(
            {Init::INFO_BUTTON_SIZE / 2.f, Init::INFO_BUTTON_SIZE / 2.f});
        _nextButton.setColor(Init::GOLD_RICH);
        _nextButton.setPosition({pos.x + Init::INFO_SIZE_X - Init::GAP -
                Init::INFO_BUTTON_SIZE / 2.f,
            pos.y});
    }
} // namespace Zappy
