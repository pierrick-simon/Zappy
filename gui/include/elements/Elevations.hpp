/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Elevation
*/

#ifndef ELEVATIONS_HPP_
    #define ELEVATIONS_HPP_

    #include <string_view>
    #include <vector>
    #include "Elevation.hpp"
    #include "Elevation2D.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/IDrawable3D.hpp"
    #include "graphics/IUpdatable.hpp"
    #include "graphics/TornadoParticle.hpp"

namespace Zappy {
    class Elevations : public Graphics::IDrawable2D,
                       public Graphics::IDrawable3D,
                       public Graphics::IUpdatable {
    public:
        Elevations();

        void addElevation(std::size_t x, std::size_t y, std::size_t level,
            std::vector<std::size_t> players, raylib::Vector2 pos);
        std::vector<std::size_t> endElevation(std::size_t x, std::size_t y);
        void removePlayer(std::size_t id);

        void update(float dt) override;
        void draw2D() const override;
        void draw3D() const override;

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
        std::vector<Parts> _elevations;
        std::vector<Graphics::TornadoParticle> _finish;

        struct ParticuleParam {
            raylib::Color color;
            float fade = 0.f;
            std::size_t emit = 0;
            std::array<raylib::Vector2, Graphics::TornadoParticle::NBPARAMETER>
                parameters;
        };

        static const std::map<std::size_t, ParticuleParam> LEVELPARAM;
    };
} // namespace Zappy

#endif /* !ELEVATIONS_HPP_ */
