/*
** EPITECH PROJECT, 2026
** gui
** File description:
** InfoBox
*/

#ifndef INFOBOX_HPP_
    #define INFOBOX_HPP_

    #include <map>
    #include <string_view>
    #include "Init.hpp"
    #include "graphics/IEvent.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Sprite2D.hpp"

namespace Zappy {
    class InfoBox : public Graphics::IEvent {
    public:
        enum class Action { LEFT, RIGHT, CLOSE, NONE };

        InfoBox(raylib::Vector2 pos, bool close = false);

        void setSize(raylib::Vector2 size);
        virtual void changeSelected(Action dir) = 0;
        void event(raylib::Camera3D &camera, const raylib::Vector2 &mouse,
            const Ray &ray, bool &leftClick) override;

    protected:
        void initSprite(raylib::Vector2 pos);
        void initSpriteInfo(raylib::Vector2 pos);

        struct Button {
            Graphics::Sprite2D sprite;
            KeyboardKey key = KEY_NULL;
        };

        Graphics::Box2D _box;
        std::map<Action, Button> _buttons;
        bool _close;

        static constexpr std::string_view IMG_CLOSE = "public/close.png";
        static constexpr float CLOSE_SIZE = 1100;
        static constexpr float CLOSE_SCALE =
            Init::INFO_BUTTON_SIZE / CLOSE_SIZE;
    };
} // namespace Zappy

#endif /* !INFOBOX_HPP_ */
