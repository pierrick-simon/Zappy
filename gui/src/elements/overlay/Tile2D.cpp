/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Tile2D
*/

#include "Tile2D.hpp"
#include "Overlay.hpp"

namespace Zappy {
    Tile2D::Tile2D(Font &font)
    {
        auto x = float(GetScreenWidth()) - Init::GAP - Init::INFO_SIZE_X;
        raylib::Vector2 pos(x, Init::INFO_POS_Y);
        initText(font, pos);
        _box.setPos(pos);
        _box.setBorderSize(Init::BORDER_SIZE);
        _box.setRound(Init::BORDER_ROUND);
        _box.setBorderColor(Init::GOLD_RICH);
        _box.setColor(Init::DARK_PINEWOOD);
    }

    void Tile2D::initText(Font &font, raylib::Vector2 pos)
    {
        pos.y += Init::GAP;
        _title.setFont(font);
        _title.setColor(Init::GOLD_RICH);
        _title.setFontSize(Init::INFO_TITLE_SIZE);
        _title.setPosition({pos.x + Init::INFO_SIZE_X / 2.f, pos.y});
        pos.x += Init::GAP;
        pos.y += Init::INFO_SMALL_GAP + Init::INFO_TITLE_SIZE;
        _text[NbPlayer].prefix = "Nb Player:";
        _text[NbEgg].prefix = "Nb Egg:";
        _text[NBElevation].prefix = "Nb Elevation:";
        _text[Resources].prefix = "Resources:";
        for (auto &text : _text) {
            while (text.prefix.size() <= Init::INFO_PREFIX_SIZE)
                text.prefix += " ";
            text.text.setFont(font);
            text.text.setFontSize(Init::INFO_TEXT_SIZE);
            text.text.setPosition(pos);
            text.color = Init::GOLD_RICH;
            pos.y += Init::INFO_SMALL_GAP + Init::INFO_TEXT_SIZE;
        }
        initResources(font, pos);
    }

    void Tile2D::initResources(Font &font, raylib::Vector2 pos)
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
            res.text.setPosition(
                {pos.x + Init::INFO_SIZE_X - Init::GAP * 7.f, pos.y});
            pos.y += Init::INFO_SMALL_GAP + Init::INFO_TEXT_SIZE;
        }
        _box.setSize({Init::INFO_SIZE_X, pos.y - Init::INFO_POS_Y + Init::GAP});
    }

    void Tile2D::update(const TileInfo &info)
    {
        _title.setStr("Tile (" + std::to_string(info.x) + "," +
            std::to_string(info.y) + ")");
        raylib::Vector2 size = _title.getSize();
        _title.setOrigin({size.x / 2.f, 0});
        auto min = std::min(info.nbPlayer, Init::INFO_MAX);
        _text[NbPlayer].value = std::to_string(min);
        min = std::min(info.nbEgg, Init::INFO_MAX);
        _text[NbEgg].value = std::to_string(min);
        min = std::min(info.nbElevation, Init::INFO_MAX);
        _text[NBElevation].value = std::to_string(min);
        updateResources(info.resources);
    }

    void Tile2D::updateResources(
        const std::map<Info::ResourceName, std::size_t> &resources)
    {
        for (const auto &[name, nb] : resources) {
            auto quantity = std::min(nb, Init::INFO_MAX);
            auto find = _resources.find(name);
            if (find != _resources.end()) {
                find->second.text.setStr(std::to_string(quantity));
                auto tmp = find->second.text.getSize();
                find->second.text.setOrigin({tmp.x, 0});
            }
        }
    }

    void Tile2D::draw2D() const
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
    }
} // namespace Zappy
