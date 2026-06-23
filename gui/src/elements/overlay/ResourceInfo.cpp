/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** ResourceInfo
*/

#include "ResourceInfo.hpp"
#include <algorithm>
#include "Init.hpp"

namespace Zappy {
    ResourceInfo::ResourceInfo(raylib::Font &font, const raylib::Vector2 &pos,
        const TextureSize &texture) :
        _pos(pos)
    {
        initRect();
        initText(font);
        initSprite(texture);
    }

    void ResourceInfo::initSprite(const TextureSize &texture)
    {
        auto ratio = Init::RESOURCE_STONE_ICON / texture.size.y;
        raylib::Vector2 origin = {
            texture.size.x * ratio / 2.f, texture.size.y * ratio / 2.f};
        _resourceIcon.Load(texture.path);
        _resourceIcon.setScale({ratio, ratio});
        _resourceIcon.setOrigin(origin);
        _resourceIcon.setPosition({_pos.x + Init::RESOURCE_ICON_POS.x,
            _pos.y + Init::RESOURCE_ICON_POS.y});
        _houseIcon.Load(HOUSE_ICON.data());
        _houseIcon.setColor(Init::GOLD_RICH);
        _houseIcon.setScale({HOUSE_RATIO, HOUSE_RATIO});
        _houseIcon.setOrigin(HOUSE_ICON_ORIGIN);
        _houseIcon.setPosition({_pos.x + Init::RESOURCE_ICON_POS.x,
            _pos.y + Init::RESOURCE_SIZE.y + Init::RESOURCE_ICON_POS.y});
        _golemIcon.Load(GOLEM_ICON.data());
        _golemIcon.setColor(Init::GOLD_RICH);
        _golemIcon.setScale({GOLEM_RATIO, GOLEM_RATIO});
        _golemIcon.setOrigin(GOLEM_ICON_ORIGIN);
        _golemIcon.setPosition({_pos.x + Init::RESOURCE_ICON_POS.x,
            _pos.y + Init::RESOURCE_SIZE.y * 2.f + Init::RESOURCE_ICON_POS.y});
    }

    void ResourceInfo::initText(raylib::Font &font)
    {
        _text.setFontSize(FONTSIZE);
        _text.setPosition({_pos.x + Init::RESOURCE_SIZE.x - Init::RESOURCE_GAP,
            _pos.y + Init::RESOURCE_SIZE.y / 2.f});
        _text.setFont(font);
        _text.setColor(Init::GOLD_RICH);
        _map.setFontSize(FONTSIZE);
        _map.setPosition({_pos.x + Init::RESOURCE_SIZE.x - Init::RESOURCE_GAP,
            _pos.y + Init::RESOURCE_SIZE.y * 1.5f});
        _map.setFont(font);
        _map.setColor(raylib::Color::White());
        _player.setFontSize(FONTSIZE);
        _player.setPosition(
            {_pos.x + Init::RESOURCE_SIZE.x - Init::RESOURCE_GAP,
                _pos.y + Init::RESOURCE_SIZE.y * 2.5f});
        _player.setFont(font);
        _player.setColor(raylib::Color::White());
    }

    void ResourceInfo::initRect()
    {
        _rec.setSize(Init::RESOURCE_SIZE);
        _rec.setPos(_pos);
        _rec.setBorderSize(Init::BORDER_SIZE);
        _rec.setRound(Init::BORDER_ROUND);
        _rec.setBorderColor(Init::GOLD_RICH);
        _rec.setColor(Init::DARK_PINEWOOD);
        _info.setSize({Init::RESOURCE_SIZE.x, Init::RESOURCE_SIZE.y * 3.f});
        _info.setPos(_pos);
        _info.setRound(Init::BORDER_ROUND);
        _info.setColor(Init::BLUE_THROUGH);
    }

    void ResourceInfo::update(std::size_t map, std::size_t players)
    {
        auto nb = std::min(map + players, MAX);
        _text.setStr(std::to_string(nb));
        auto tmp = _text.getSize();
        _text.setOrigin({tmp.x, tmp.y / 2.f});
        nb = std::min(map, MAX);
        _map.setStr(std::to_string(nb));
        tmp = _map.getSize();
        _map.setOrigin({tmp.x, tmp.y / 2.f});
        nb = std::min(players, MAX);
        _player.setStr(std::to_string(nb));
        tmp = _player.getSize();
        _player.setOrigin({tmp.x, tmp.y / 2.f});
    }

    void ResourceInfo::draw2D() const
    {
        _info.draw2D();
        _rec.draw2D();
        _text.draw2D();
        _map.draw2D();
        _player.draw2D();
        _resourceIcon.draw2D();
        _houseIcon.draw2D();
        _golemIcon.draw2D();
    }
} // namespace Zappy
