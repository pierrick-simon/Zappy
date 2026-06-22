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
        Font &font, std::unordered_map<std::string, Color> &teams) :
        _teams(teams)
    {
        auto x = float(GetScreenWidth()) - Init::GAP - SIZE_X;
        Vector2 pos(x, POS_Y);
        initText(font, pos);
        _box.setPos(pos);
        _box.setBorderSize(Init::BORDER_SIZE);
        _box.setRound(Init::BORDER_ROUND);
        _box.setBorderColor(Init::GOLD_RICH);
        _box.setColor(Init::DARK_PINEWOOD);
    }

    void Player2D::initText(Font &font, Vector2 pos)
    {
        pos.y += Init::GAP;
        _title.setFont(font);
        _title.setColor(Init::GOLD_RICH);
        _title.setFontSize(TITLE_SIZE);
        _title.setPosition({pos.x + SIZE_X / 2.f, pos.y});
        pos.x += Init::GAP;
        pos.y += SMALL_GAP + TITLE_SIZE;
        for (auto &text : _text) {
            text.setFont(font);
            text.setColor(WHITE);
            text.setFontSize(TEXT_SIZE);
            text.setPosition(pos);
            pos.y += SMALL_GAP + TEXT_SIZE;
        }
        initTeamName(font);
        initInventory(font, pos);
    }

    void Player2D::initInventory(Font &font, Vector2 pos)
    {
        pos.x += Init::GAP * 2.f;
        for (const auto &[name, info] : Overlay::RESOURCES) {
            auto ratio = ICON / info.size.y;
            Vector2 origin = {
                info.size.x * ratio / 2.f, info.size.y * ratio / 2.f};
            auto &[_, res] = *_resources.try_emplace(name).first;
            res.sprite.Load(info.path);
            res.sprite.setColor(Init::GOLD_RICH);
            res.sprite.setScale({ratio, ratio});
            res.sprite.setOrigin(origin);
            res.sprite.setPosition({pos.x + ICON_POS.x, pos.y + ICON_POS.y});
            res.text.setFont(font);
            res.text.setColor(Init::GOLD_RICH);
            res.text.setFontSize(TEXT_SIZE);
            res.text.setPosition({pos.x + SIZE_X - Init::GAP * 7.f, pos.y});
            pos.y += SMALL_GAP + TEXT_SIZE;
        }
        _text[Inventory].setStr("Inventory: ");
        _box.setSize({SIZE_X, pos.y - POS_Y + Init::GAP});
    }

    void Player2D::initTeamName(Font &font)
    {
        _text[Team].setStr("Team: ");
        _teamName.setFont(font);
        _teamName.setFontSize(TEXT_SIZE);
        Vector2 pos = _text[Team].getPosition();
        Vector2 size = _text[Team].getSize();
        pos.x += size.x;
        _teamName.setPosition(pos);
    }

    void Player2D::update(const PlayerInfo &info)
    {
        _title.setStr("Player " + std::to_string(info.id));
        Vector2 size = _title.getSize();
        _title.setOrigin({size.x / 2.f, 0});
        updateTeamName(info.team);
        _text[Level].setStr("Level: " + std::to_string(info.level));
        _text[Position].setStr("Pos: (" + std::to_string(info.x) + "," +
            std::to_string(info.y) + ")");
        _text[Status].setStr("Status: " + PlayerStatus::getMsg(info.status));
        Vector2 pos = _text[Team].getPosition();
        size = _text[Team].getSize();
        pos.x += size.x;
        _teamName.setPosition(pos);
        updateInventory(info.inventory);
    }

    void Player2D::updateInventory(
        const std::map<Info::ResourceName, std::size_t> &inventory)
    {
        for (const auto &[name, nb] : inventory) {
            auto quantity = std::min(nb, MAX);
            auto find = _resources.find(name);
            if (find != _resources.end()) {
                find->second.text.setStr(std::to_string(quantity));
                auto tmp = find->second.text.getSize();
                find->second.text.setOrigin({tmp.x, 0});
            }
        }
    }

    void Player2D::updateTeamName(const std::string &team)
    {
        _teamName.setStr(team);
        if (_teams.contains(team))
            _teamName.setColor(_teams.at(team));
        std::string name(team);
        bool first = true;
        auto size_x = _teamName.getSize().x;
        auto maxSize_x =
            float(GetScreenWidth()) - Init::GAP - _teamName.getPosition().x;
        while (size_x > maxSize_x) {
            name.pop_back();
            _teamName.setStr(name + "...");
            size_x = _teamName.getSize().x;
        }
    }

    void Player2D::draw2D() const
    {
        _box.draw2D();
        _title.draw2D();
        for (const auto &text : _text)
            text.draw2D();
        _teamName.draw2D();
        for (const auto &[_, info] : _resources) {
            info.sprite.draw2D();
            info.text.draw2D();
        }
    }
} // namespace Zappy
