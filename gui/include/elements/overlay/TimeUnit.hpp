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
    #include "graphics/IEvent.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Sprite2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class TimeUnit : public Graphics::IDrawable2D, public Graphics::IEvent {
    public:
        TimeUnit(raylib::Font &font);

        void draw2D() const override;
        std::size_t update(std::size_t timeUnit);
        void event(raylib::Camera3D &camera, const raylib::Vector2 &mouse,
            const Ray &ray, bool &leftClick) override;

    private:
        enum Action { FASTLEFT, LEFT, FASTRIGHT, RIGHT, NBBUTTON, NONE };

        void initSprite(raylib::Vector2 pos);
        void initSpriteInfo(raylib::Vector2 pos);
        std::size_t changeTimeUnit(Action button, std::size_t frequency);

        struct Button {
            Graphics::Sprite2D sprite;
            KeyboardKey key = KEY_NULL;
        };

        Graphics::Box2D _box;
        Graphics::Text2D _text;
        std::array<Button, NBBUTTON> _sprites;
        Action _button = Action::NONE;

        static const std::array<std::string, NBBUTTON> PATH;

        static constexpr raylib::Vector2 SIZE = {200, 40};
        static constexpr float TEXT_SIZE = 30;
        static constexpr std::size_t MAX_FREQUENCY = 100;
        static constexpr std::size_t MIN_FREQUENCY = 1;
        static constexpr std::size_t MOVE_GAP = 10;
    };
} // namespace Zappy

#endif /* !TIMEUNIT_HPP_ */
