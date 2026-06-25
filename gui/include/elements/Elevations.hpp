/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Elevation
*/

#ifndef ELEVATIONS_HPP_
    #define ELEVATIONS_HPP_

    #include <list>
    #include <string_view>
    #include "Elevation.hpp"
    #include "Elevation2D.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/IDrawable3D.hpp"
    #include "graphics/IEvent.hpp"
    #include "graphics/IUpdatable.hpp"
    #include "graphics/TornadoParticle.hpp"

namespace Zappy {
    class Elevations : public Graphics::IDrawable2D,
                       public Graphics::IDrawable3D,
                       public Graphics::IUpdatable,
                       public Graphics::IEvent {
    public:
        Elevations(std::optional<std::size_t> &selectPlayer,
            std::optional<std::size_t> &selectTile, std::size_t &width,
            std::size_t &timeUnit);

        void addElevation(std::size_t x, std::size_t y, std::size_t level,
            std::vector<std::size_t> players, Vector2 pos);
        std::vector<std::size_t> endElevation(std::size_t x, std::size_t y);
        void removePlayer(std::size_t id);

        void update(float dt) override;
        void draw2D() const override;
        void draw3D() const override;
        void event(raylib::Camera3D &camera, const raylib::Vector2 &mouse,
            const Ray &ray, bool &leftClick) override;

        [[nodiscard]] std::size_t getNbTileElevations(
            std::size_t tile, std::size_t mapWidth) const;

    private:
        struct Parts {
            Elevation info;
            Elevation2D overlay;
            Graphics::TornadoParticle particle;
            std::size_t emit = 0;
        };

        raylib::Font _font;
        std::list<Parts> _elevations;
        std::list<Graphics::TornadoParticle> _finish;

        struct ParticuleParam {
            raylib::Color color;
            float fade = 0.f;
            std::size_t emit = 0;
            std::array<raylib::Vector2, Graphics::TornadoParticle::NBPARAMETER>
                parameters;
        };

        std::optional<std::size_t> &_selectPlayer;
        std::optional<std::size_t> &_selectTile;
        std::size_t &_width;
        std::size_t &_timeUnit;

        static const std::map<std::size_t, ParticuleParam> LEVELPARAM;
        static constexpr std::size_t NBLEVEL = 8;
        static constexpr float RATIOPARTICLE = 300.f / NBLEVEL;
    };
} // namespace Zappy

#endif /* !ELEVATIONS_HPP_ */
