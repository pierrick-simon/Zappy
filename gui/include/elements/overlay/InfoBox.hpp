/*
** EPITECH PROJECT, 2026
** gui
** File description:
** InfoBox
*/

#ifndef INFOBOX_HPP_
    #define INFOBOX_HPP_

    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Sprite2D.hpp"

namespace Zappy {
    class InfoBox {
    public:
        enum class Direction { Left, Right, None };

        InfoBox(raylib::Vector2 pos);

        void setSize(raylib::Vector2 size);
        virtual void changeSelected(Direction dir) = 0;

    protected:
        void initSprite(raylib::Vector2 pos);

        Graphics::Box2D _box;
        Graphics::Sprite2D _prevButton;
        Graphics::Sprite2D _nextButton;
    };
} // namespace Zappy

#endif /* !INFOBOX_HPP_ */
