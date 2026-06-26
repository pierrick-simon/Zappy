/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** End
*/

#include "End.hpp"
#include <iostream>

namespace Zappy {
    End::End(raylib::Font &font, std::map<std::string, raylib::Color> &teams,
        bool &quit) :
        _teams(teams), _quit(quit)
    {
        _box.setPos(START_POS);
        _box.setBorderSize(Init::BORDER_SIZE);
        _box.setRound(Init::BORDER_ROUND);
        _box.setBorderColor(Init::GOLD_RICH);
        _box.setColor(Init::DARK_PINEWOOD);
        _box.setSize(SIZE);
        initText(font);
        initButton(font);
    }

    void End::draw2D() const
    {
        _box.draw2D();
        _text.draw2D();
        _team.draw2D();
        _button.draw2D();
        _buttonText.draw2D();
    }

    void End::initText(raylib::Font &font)
    {
        auto height = START_POS.y + Init::GAP * 2.f;
        _text.setFont(font);
        _text.setColor(Init::GOLD_RICH);
        _text.setFontSize(TEXT_SIZE);
        _text.setPosition({Init::WINDOW_SIZE_X / 2.f, height});
        _text.setStr("The Wining team is :");
        auto tmp = _text.getSize();
        _text.setOrigin({tmp.x / 2.f, 0});
        height += Init::GAP * 2.f + TEXT_SIZE;
        _team.setFont(font);
        _team.setFontSize(TEXT_SIZE);
        _team.setPosition({Init::WINDOW_SIZE_X / 2.f, height});
    }

    void End::initButton(raylib::Font &font)
    {
        _button.setPos(BUTTON_POS);
        _button.setBorderSize(Init::BORDER_SIZE);
        _button.setRound(Init::BORDER_ROUND);
        _button.setBorderColor(Init::GOLD_RICH);
        _button.setColor(Init::DARK_PINEWOOD);
        _button.setSize(BUTTON_SIZE);
        _buttonText.setFont(font);
        _buttonText.setColor(Init::GOLD_RICH);
        _buttonText.setFontSize(TEXT_SIZE);
        _buttonText.setPosition(
            {Init::WINDOW_SIZE_X / 2.f, BUTTON_POS.y + Init::GAP});
        _buttonText.setStr("Quit");
        auto tmp = _buttonText.getSize();
        _buttonText.setOrigin({tmp.x / 2.f, 0});
    }

    void End::win(const std::string &team)
    {
        _team.setStr(team);
        if (_teams.contains(team))
            _team.setColor(_teams.at(team));
        std::string name(team);
        bool first = true;
        auto size_x = _team.getSize().x;
        auto maxSize_x = SIZE.x - Init::GAP * 2.f;
        while (size_x > maxSize_x) {
            name.pop_back();
            _team.setStr(name + "...");
            size_x = _team.getSize().x;
        }
        _team.setOrigin({size_x / 2.f, 0});
    }

    void End::event(raylib::Camera3D &camera, const raylib::Vector2 &mouse,
        const Ray &ray, bool &leftClick)
    {
        if (leftClick && _button.checkCollision(mouse))
            _quit = true;
    }
} // namespace Zappy
