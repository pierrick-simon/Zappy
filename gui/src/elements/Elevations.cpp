/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Elevations
*/

#include "Elevations.hpp"
#include "Init.hpp"

namespace Zappy {
    Elevations::Elevations() :
        _font(LoadFont(Init::FONT_PATH.data()))
    {
    }

    void Elevations::addElevation(std::size_t x, std::size_t y,
        std::size_t level, std::vector<std::size_t> players)
    {
        _elevations.emplace_back(Elevation {x, y, level, std::move(players)},
            Elevation2D {_font, x, y, level});
    }

    std::vector<std::size_t> Elevations::endElevation(
        std::size_t x, std::size_t y)
    {
        std::vector<std::size_t> ids;
        for (auto iter = _elevations.begin(); iter != _elevations.end();
            iter++) {
            auto &info = iter->info;
            if (info.getX() == x && info.getY() == y) {
                ids = info.getPlayers();
                _elevations.erase(iter);
                break;
            }
        }
        return ids;
    }

    void Elevations::removePlayer(std::size_t id)
    {
        for (auto &[elevation, _] : _elevations)
            elevation.removePlayer(id);
    }

    void Elevations::update(float dt)
    {
        auto pos = Init::INCANTATION_START_POS;
        for (auto &[_, elevation] : _elevations) {
            elevation.update(dt);
            elevation.setPos(pos);
            pos.y += Init::INCANTATION_SIZE.y + Init::INCANTATION_GAP;
        }
    }

    void Elevations::draw2D() const
    {
        std::size_t i = 0;
        for (const auto &[_, elevation] : _elevations) {
            if (i >= Init::INCANTATION_MAX_DISPLAY)
                break;
            elevation.draw2D();
            i++;
        }
    }

    std::size_t Elevations::getNbTileElevations(
        std::size_t tile, std::size_t width) const
    {
        std::size_t nb = 0;
        for (const auto &[elevation, _] : _elevations) {
            if (elevation.getTile(width) == tile)
                nb++;
        }
        return nb;
    }
} // namespace Zappy
