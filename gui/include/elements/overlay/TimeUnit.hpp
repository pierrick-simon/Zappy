/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** TimeUnit
*/

#ifndef TIMEUNIT_HPP_
    #define TIMEUNIT_HPP_

    #include <array>
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Sprite2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class TimeUnit : public Graphics::IDrawable2D {
    public:
        TimeUnit(raylib::Font &font);

        void draw2D() const override;
        std::size_t update(std::size_t timeUnit);

    private:
        enum Button { FastLeft, Left, FastRight, Right, NbButton, None };

        void initSprite(raylib::Vector2 pos);
        std::size_t changeTimeUnit(Button button, std::size_t frequency);

        Graphics::Box2D _box;
        Graphics::Text2D _text;
        std::array<Graphics::Sprite2D, NbButton> _sprites;
        Button _button = Button::None;

        static const std::array<std::string, NbButton> PATH;

        static constexpr raylib::Vector2 SIZE = {200, 40};
        static constexpr float TEXT_SIZE = 30;
        static constexpr std::size_t MAX_FREQUENCY = 100;
        static constexpr std::size_t MIN_FREQUENCY = 1;
        static constexpr std::size_t MOVE_GAP = 10;
    };
} // namespace Zappy

#endif /* !TIMEUNIT_HPP_ */
