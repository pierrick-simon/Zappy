/*
** EPITECH PROJECT, 2026
** gui
** File description:
** Box
*/

#ifndef BOX2D_HPP_
    #define BOX2D_HPP_

    #include "Init.hpp"
    #include "graphics/UiObject.hpp"
    #include "graphics/primitives/Rectangle2D.hpp"

namespace Graphics {
    class Box2D : public UiObject {
    public:
        Box2D() = default;

        void setBorderSize(float size);
        void setBorderColor(raylib::Color color);
        void setColor(raylib::Color color);
        void setSize(Vector2 size);
        void setPos(Vector2 pos);
        void setRound(float round);
        void setSegement(int segment);

        void draw2D() const override;

    private:
        void update();

        float _borderSize = 0;
        raylib::Vector2 _size = {0, 0};
        raylib::Vector2 _pos = {0, 0};
        Rectangle2D _box;
        Rectangle2D _border;
        raylib::Color _color = raylib::Color::White();
        raylib::Color _borderColor = raylib::Color::White();
        float _round = 0;
        int _segment = 0;
    };
} // namespace Graphics

#endif /* !BOX2D_HPP_ */
