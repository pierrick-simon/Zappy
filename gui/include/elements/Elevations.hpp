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
    #include "graphics/IUpdatable.hpp"

namespace Zappy {
    class Elevations : public Graphics::IDrawable2D,
                       public Graphics::IUpdatable {
    public:
        Elevations();

        void addElevation(std::size_t x, std::size_t y, std::size_t level,
            std::vector<std::size_t> players);
        std::vector<std::size_t> endElevation(std::size_t x, std::size_t y);
        void removePlayer(std::size_t id);

        void update(float dt) override;
        void draw2D() const override;

    private:
        struct Parts {
            Elevation info;
            Elevation2D overlay;
        };

        Font _font;
        std::vector<Parts> _elevations;
    };
} // namespace Zappy

#endif /* !ELEVATIONS_HPP_ */
