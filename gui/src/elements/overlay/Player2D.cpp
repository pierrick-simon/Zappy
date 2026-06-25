/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Player2D
*/

#include "Player2D.hpp"
#include "Overlay.hpp"

namespace Zappy {
    Player2D::Player2D(
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

    void Player2D::initText(raylib::Font &font, raylib::Vector2 pos)
    {
        pos.y += Init::GAP;
        _title.setFont(font);
        _title.setColor(Init::GOLD_RICH);
        _title.setFontSize(Init::INFO_TITLE_SIZE);
        _title.setPosition({pos.x + Init::INFO_SIZE_X / 2.f, pos.y});
        pos.x += Init::GAP;
        pos.y += Init::INFO_SMALL_GAP + Init::INFO_TITLE_SIZE;
        for (auto &text : _text) {
            text.text.setFont(font);
            text.text.setFontSize(Init::INFO_TEXT_SIZE);
            text.text.setPosition(pos);
            text.color = Init::GOLD_RICH;
            pos.y += Init::INFO_SMALL_GAP + Init::INFO_TEXT_SIZE;
        }
        _text[TEAM].prefix = "Team: ";
        _text[LEVEL].prefix = "Level: ";
        _text[POSITION].prefix = "Pos: ";
        _text[STATUS].prefix = "Satus: ";
        _text[INVENTORY].prefix = "Inventory: ";
        initInventory(font, pos);
    }

    void Player2D::initInventory(raylib::Font &font, raylib::Vector2 pos)
    {
        pos.x += Init::GAP * 2.f;
        for (const auto &[name, info] : Overlay::RESOURCES) {
            auto ratio = Init::INFO_ICON / info.size.y;
            raylib::Vector2 origin = {
                info.size.x * ratio / 2.f, info.size.y * ratio / 2.f};
            auto &[_, res] = *_resources.try_emplace(name).first;
            res.sprite.Load(info.path);
            res.sprite.setScale({ratio, ratio});
            res.sprite.setOrigin(origin);
            res.sprite.setPosition(
                {pos.x + Init::INFO_ICON_POS.x, pos.y + Init::INFO_ICON_POS.y});
            res.text.setFont(font);
            res.text.setColor(Init::GOLD_RICH);
            res.text.setFontSize(Init::INFO_TEXT_SIZE);
            res.text.setPosition({pos.x + Init::INFO_SIZE_X - Init::GAP * 7.f,
                pos.y + Init::INFO_ICON_POS.y});
            pos.y += Init::INFO_SMALL_GAP + Init::INFO_TEXT_SIZE;
        }
        setSize({Init::INFO_SIZE_X, pos.y - Init::INFO_POS_Y + Init::GAP});
    }

    InfoBox::Action Player2D::update(const PlayerInfo &info)
    {
        _title.setStr("Player " + std::to_string(info.id));
        raylib::Vector2 size = _title.getSize();
        _title.setOrigin({size.x / 2.f, 0});
        updateTeamName(info.team);
        _text[LEVEL].value = std::to_string(info.level);
        _text[POSITION].value =
            "(" + std::to_string(info.x) + "," + std::to_string(info.y) + ")";
        _text[STATUS].value = PlayerStatus::getMsg(info.status);
        updateInventory(info.inventory);
        auto dir = _dir;
        _dir = Action::NONE;
        return dir;
    }

    void Player2D::updateInventory(
        const std::map<Info::ResourceName, std::size_t> &inventory)
    {
        for (const auto &[name, nb] : inventory) {
            auto quantity = std::min(nb, Init::INFO_MAX);
            auto find = _resources.find(name);
            if (find != _resources.end()) {
                find->second.text.setStr(std::to_string(quantity));
                auto tmp = find->second.text.getSize();
                find->second.text.setOrigin({tmp.x, tmp.y / 2.f});
            }
        }
    }

    void Player2D::updateTeamName(const std::string &team)
    {
        _text[TEAM].value = team;
        if (_teams.contains(team))
            _text[TEAM].color = _teams.at(team);
        bool first = true;
        auto maxSize_x = float(Init::WINDOW_SIZE_X) - Init::GAP -
            _text[TEAM].text.getPosition().x;
        _text[TEAM].text.setStr(_text[TEAM].prefix + _text[TEAM].value);
        auto size_x = _text[TEAM].text.getSize().x;
        bool enter = false;
        while (size_x > maxSize_x) {
            _text[TEAM].value.pop_back();
            _text[TEAM].text.setStr(
                _text[TEAM].prefix + _text[TEAM].value + "...");
            size_x = _text[TEAM].text.getSize().x;
            enter = true;
        }
        if (enter)
            _text[TEAM].value += "...";
    }

    void Player2D::draw2D() const
    {
        _box.draw2D();
        _title.draw2D();
        for (auto &text : _text)
            Graphics::Text2D::drawMultiColorStrs(
                text.text, {{text.prefix}, {text.value, text.color}});
        for (const auto &[_, info] : _resources) {
            info.sprite.draw2D();
            info.text.draw2D();
        }
        for (const auto &[_, button] : _buttons)
            button.sprite.draw2D();
    }

    void Player2D::changeSelected(Action dir)
    {
        _dir = dir;
    }
} // namespace Zappy
