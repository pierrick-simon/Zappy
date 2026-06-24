/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Elevations
*/

#include "Elevations.hpp"
#include "Init.hpp"
#include "Map.hpp"

namespace Zappy {
    Elevations::Elevations() :
        _font(Init::FONT_PATH.data())
    {
    }

    void Elevations::addElevation(std::size_t x, std::size_t y,
        std::size_t level, std::vector<std::size_t> players, Vector2 pos)
    {
        auto param = LEVELPARAM.begin()->second;
        if (LEVELPARAM.contains(level))
            param = LEVELPARAM.find(level)->second;
        auto &part = _elevations.emplace_back(
            Elevation {x, y, level, std::move(players)},
            Elevation2D {_font, x, y, level},
            Graphics::TornadoParticle {
                param.color, param.fade, param.parameters},
            param.emit);
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
            elevation.particle.emit(elevation.emit);
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

    const std::map<std::size_t, Elevations::ParticuleParam>
        Elevations::LEVELPARAM = {
            {1,
                {raylib::Color {100, 200, 255, 255},
                    0.3f,
                    5,
                    {{
                        {Map::TILE_WIDTH * 0.02f, Map::TILE_WIDTH * 0.10f},
                        {0.10f, 0.25f},
                        {0.10f, 0.20f},
                        {5.0f, 10.0f},
                        {0.03f, 0.07f},
                        {-20.f, 20.f},
                    }}}},
            {2,
                {raylib::Color {50, 255, 120, 255},
                    0.3f,
                    8,
                    {{
                        {Map::TILE_WIDTH * 0.04f, Map::TILE_WIDTH * 0.14f},
                        {0.15f, 0.30f},
                        {0.15f, 0.30f},
                        {8.0f, 15.0f},
                        {0.04f, 0.09f},
                        {-20.f, 20.f},
                    }}}},
            {3,
                {raylib::Color {255, 220, 0, 255},
                    0.3f,
                    10,
                    {{
                        {Map::TILE_WIDTH * 0.06f, Map::TILE_WIDTH * 0.18f},
                        {0.20f, 0.40f},
                        {0.20f, 0.40f},
                        {10.0f, 20.0f},
                        {0.05f, 0.10f},
                        {-25.f, 25.f},
                    }}}},
            {4,
                {raylib::Color {255, 140, 0, 255},
                    0.3f,
                    12,
                    {{
                        {Map::TILE_WIDTH * 0.08f, Map::TILE_WIDTH * 0.22f},
                        {0.25f, 0.50f},
                        {0.25f, 0.50f},
                        {12.0f, 22.0f},
                        {0.06f, 0.11f},
                        {-25.f, 25.f},
                    }}}},
            {5,
                {raylib::Color {255, 60, 0, 255},
                    0.3f,
                    15,
                    {{
                        {Map::TILE_WIDTH * 0.10f, Map::TILE_WIDTH * 0.30f},
                        {0.30f, 0.60f},
                        {0.30f, 0.60f},
                        {15.0f, 25.0f},
                        {0.07f, 0.13f},
                        {-30.f, 30.f},
                    }}}},
            {6,
                {raylib::Color {180, 0, 255, 255},
                    0.3f,
                    18,
                    {{
                        {Map::TILE_WIDTH * 0.12f, Map::TILE_WIDTH * 0.36f},
                        {0.40f, 0.70f},
                        {0.40f, 0.70f},
                        {18.0f, 30.0f},
                        {0.08f, 0.14f},
                        {-30.f, 30.f},
                    }}}},
            {7,
                {raylib::Color {255, 255, 255, 255},
                    0.4f,
                    20,
                    {{
                        {Map::TILE_WIDTH * 0.16f, Map::TILE_WIDTH * 0.40f},
                        {0.50f, 0.80f},
                        {0.50f, 0.90f},
                        {20.0f, 35.0f},
                        {0.09f, 0.16f},
                        {-30.f, 30.f},
                    }}}},
            {8,
                {raylib::Color {255, 220, 100, 255},
                    0.5f,
                    25,
                    {{
                        {Map::TILE_WIDTH * 0.20f, Map::TILE_WIDTH * 0.48f},
                        {0.60f, 1.00f},
                        {0.60f, 1.20f},
                        {25.0f, 40.0f},
                        {0.10f, 0.18f},
                        {-30.f, 30.f},
                    }}}},
    };
} // namespace Zappy
