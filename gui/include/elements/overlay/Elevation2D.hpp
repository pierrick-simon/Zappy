/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Elevation2D
*/

#ifndef ELEVATION2D_HPP_
    #define ELEVATION2D_HPP_

    #include <map>
    #include "Init.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/IUpdatable.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class Elevation2D : public Graphics::IDrawable2D,
                        public Graphics::IUpdatable {
    public:
        Elevation2D(raylib::Font &font, std::size_t x, std::size_t y,
            std::size_t level);

        void update(float dt) override;
        void draw2D() const override;

        void setPos(Vector2 pos);

    private:
        void initText(raylib::Font &font, std::size_t x, std::size_t y,
            std::size_t level);
        void initRect();

        Graphics::Text2D _titleText;
        Graphics::Text2D _levelText;
        Graphics::Text2D _posText;
        Graphics::Box2D _box;
        Graphics::Box2D _status;

        float _timer = 0.f;

        static constexpr float TITLE_SIZE = 30;
        static constexpr float TEXT_SIZE = 25;
        static constexpr float SMALL_GAP = 5;
        static constexpr float TIME = 300;
        static constexpr float SATUS_HEGHT = 20;
    };
} // namespace Zappy

#endif /* !ELEVATION2D_HPP_ */
