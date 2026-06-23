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
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Sprite2D.hpp"

namespace Zappy {
    class InfoBox {
    public:
        enum class Action { Left, Right, Close, None };

        InfoBox(raylib::Vector2 pos, bool close = false);

        void setSize(raylib::Vector2 size);
        virtual void changeSelected(Action dir) = 0;

    protected:
        void initSprite(raylib::Vector2 pos);
        void initSpriteInfo(raylib::Vector2 pos);

        Graphics::Box2D _box;
        std::map<Action, Graphics::Sprite2D> _buttons;
        bool _close;

        static constexpr std::string_view IMG_CLOSE = "public/close.png";
        static constexpr float CLOSE_SIZE = 1100;
        static constexpr float CLOSE_SCALE =
            Init::INFO_BUTTON_SIZE / CLOSE_SIZE;
    };
} // namespace Zappy

#endif /* !INFOBOX_HPP_ */
