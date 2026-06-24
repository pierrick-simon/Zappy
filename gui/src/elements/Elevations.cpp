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
        _font(Init::FONT_PATH.data())
    {
    }

    void Elevations::addElevation(std::size_t x, std::size_t y,
        std::size_t level, std::vector<std::size_t> players, Vector2 pos)
    {
        auto &part = _elevations.emplace_back(
            Elevation {x, y, level, std::move(players)},
            Elevation2D {_font, x, y, level},
            Graphics::TornadoParticle {Init::GOLD_RICH});
        part.particle.setPosition({pos.x, 0, pos.y});
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
                _finish.emplace_back(std::move(iter->particle));
                _elevations.erase(iter);
                break;
            }
        }
        return ids;
    }

    void Elevations::removePlayer(std::size_t id)
    {
        for (auto &elevation : _elevations)
            elevation.info.removePlayer(id);
    }

    void Elevations::update(float dt)
    {
        auto pos = Init::INCANTATION_START_POS;
        for (auto &elevation : _elevations) {
            elevation.overlay.update(dt);
            elevation.overlay.setPos(pos);
            pos.y += Init::INCANTATION_SIZE.y + Init::INCANTATION_GAP;
            elevation.particle.update(dt);
            elevation.particle.emit(EMIT_PARTICLES);
        }
        for (auto iter = _finish.begin(); iter != _finish.end();) {
            iter->update(dt);
            if (iter->isEmpty())
                iter = _finish.erase(iter);
            else
                iter++;
        }
    }

    void Elevations::draw2D() const
    {
        std::size_t i = 0;
        for (const auto &elevation : _elevations) {
            if (i >= Init::INCANTATION_MAX_DISPLAY)
                break;
            elevation.overlay.draw2D();
            i++;
        }
    }

    void Elevations::draw3D() const
    {
        for (const auto &elevation : _elevations)
            elevation.particle.draw3D();
        for (const auto &particle : _finish)
            particle.draw3D();
    }

    std::size_t Elevations::getNbTileElevations(
        std::size_t tile, std::size_t mapWidth) const
    {
        std::size_t nb = 0;
        for (const auto &elevation : _elevations) {
            if (elevation.info.getTile(mapWidth) == tile)
                nb++;
        }
        return nb;
    }
} // namespace Zappy
