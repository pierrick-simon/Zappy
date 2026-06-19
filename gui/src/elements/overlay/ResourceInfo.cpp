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
    ResourceInfo::ResourceInfo(Font &font, const Vector2 &pos) :
        _pos(pos), _font(font)
    {
        _text.setSpacing(2);
        _text.setFontSize(FONTSIZE);
        _text.setPos(
            {pos.x + Init::RESOURCE_SIZE.x - Init::RESOURCE_GAP, pos.y});
        _text.setFont(_font);
        _text.setColor(Init::GOLD_RICH);
        _rec.setSize(Init::RESOURCE_SIZE);
        _rec.setPos(pos);
        _rec.setBorderSize(Init::BORDER_SIZE);
        _rec.setRound(Init::BORDER_ROUND);
        _rec.setBorderColor(Init::GOLD_RICH);
        _rec.setColor(Init::DARK_PINEWOOD);
    }

    void ResourceInfo::update(std::size_t map, std::size_t players)
    {
        auto nb = std::clamp(map + players, std::size_t(0), MAX);
        _text.setStr(std::to_string(nb));
        auto tmp = _text.getSize();
        _text.setOrigin({tmp.x, 0});
    }

    void ResourceInfo::draw2D() const
    {
        _rec.draw2D();
        _text.draw2D();
    }
} // namespace Zappy
