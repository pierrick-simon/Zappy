/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Team
*/

#include "Team.hpp"
#include "Init.hpp"

namespace Zappy {
    Team::Team(
        raylib::Font &font, std::map<std::string, raylib::Color> &teams) :
        InfoBox({float(Init::WINDOW_SIZE_X) - Init::GAP - Init::INFO_SIZE_X,
                    Init::INFO_POS_Y},
            false),
        _teams(teams)
    {
        auto x = float(Init::WINDOW_SIZE_X) - Init::GAP - Init::INFO_SIZE_X;
        raylib::Vector2 pos(x, Init::INFO_POS_Y);
        initText(font, pos);
    }

    void Team::initText(raylib::Font &font, raylib::Vector2 pos)
    {
        pos.y += Init::GAP;
        _title.setFont(font);
        _title.setFontSize(Init::INFO_TITLE_SIZE);
        _title.setPosition({pos.x + Init::INFO_SIZE_X / 2.f, pos.y});
        pos.x += Init::GAP;
        pos.y += Init::INFO_SMALL_GAP + Init::INFO_TITLE_SIZE;
        _text[NBPLAYER].prefix = "Nb Player: ";
        _text[NBEGG].prefix = "Nb Egg: ";
        _text[LEVEL].prefix = "Members' Level: ";
        for (auto &text : _text) {
            text.text.setFont(font);
            text.text.setFontSize(Init::INFO_TEXT_SIZE);
            text.text.setPosition(pos);
            pos.y += Init::INFO_SMALL_GAP + Init::INFO_TEXT_SIZE;
        }
        pos.x += Init::GAP * 2.0;
        for (std::size_t i = 0; i < NB_LEVEL; i++) {
            _levels[i].text.setFont(font);
            _levels[i].text.setFontSize(Init::INFO_TEXT_SIZE);
            _levels[i].text.setPosition(pos);
            _levels[i].prefix = "Level " + std::to_string(i + 1) + ": ";
            pos.y += Init::INFO_SMALL_GAP + Init::INFO_TEXT_SIZE;
        }
        setSize({Init::INFO_SIZE_X, pos.y - Init::INFO_POS_Y + Init::GAP});
    }

    void Team::update(const TeamInfo &info)
    {
        if (!_selectTeam)
            changeSelected(Action::LEFT);
        updateMembers(info.level);
        auto min = std::min(info.nbEgg, Init::INFO_MAX);
        _text[NBEGG].value = std::to_string(min);
    }

    void Team::updateTitle(const std::string &team)
    {
        _title.setStr(team);
        if (_teams.contains(team))
            _title.setColor(_teams.at(team));
        std::string name(team);
        bool first = true;
        auto size_x = _title.getSize().x;
        auto maxSize_x = Init::INFO_SIZE_X -
            (Init::GAP + Init::INFO_SMALL_GAP + Init::INFO_BUTTON_SIZE) * 2.f;
        while (size_x > maxSize_x) {
            name.pop_back();
            _title.setStr(name + "...");
            size_x = _title.getSize().x;
        }
        _title.setOrigin({size_x / 2.f, 0});
    }

    void Team::updateMembers(const std::array<std::size_t, NB_LEVEL> &levels)
    {
        std::size_t nbPlayer = 0;
        for (std::size_t i = 0; i < NB_LEVEL; i++) {
            auto min = std::min(levels[i], Init::INFO_MAX);
            _levels[i].value = std::to_string(min);
            nbPlayer += levels[i];
        }
        auto min = std::min(nbPlayer, Init::INFO_MAX);
        _text[NBPLAYER].value = std::to_string(min);
    }

    void Team::draw2D() const
    {
        _box.draw2D();
        _title.draw2D();
        for (auto &text : _text)
            Graphics::Text2D::drawMultiColorStrs(
                text.text, {{text.prefix}, {text.value, Init::GOLD_RICH}});
        for (const auto &level : _levels)
            Graphics::Text2D::drawMultiColorStrs(
                level.text, {{level.prefix}, {level.value, Init::GOLD_RICH}});
        for (const auto &[_, button] : _buttons)
            button.sprite.draw2D();
    }

    void Team::setSelectTeam(const std::string &team)
    {
        _selectTeam = team;
        updateTitle(team);
    }

    void Team::changeSelected(Action dir)
    {
        auto find = _teams.begin();
        if (_selectTeam)
            find = _teams.find(*_selectTeam);
        if (find == _teams.end()) {
            if (!_teams.empty())
                _selectTeam = _teams.begin()->first;
            return;
        }
        if (dir == Action::LEFT) {
            if (find == _teams.begin())
                _selectTeam = _teams.rbegin()->first;
            else
                _selectTeam = (--find)->first;
        } else if (dir == Action::RIGHT) {
            if (find == --_teams.end())
                _selectTeam = _teams.begin()->first;
            else
                _selectTeam = (++find)->first;
        }
        updateTitle(*_selectTeam);
    }
} // namespace Zappy
