/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef TEXT2D_HPP
    #define TEXT2D_HPP

    #include <memory>
    #include <optional>
    #include <vector>
    #include "Init.hpp"
    #include "Text.hpp"
    #include "graphics/UiObject.hpp"

namespace Graphics {

    class Text2D : public UiObject {
    public:
        Text2D() = default;
        void draw2D() const override;

        void setFont(raylib::Font &font);
        void setStr(std::string str);
        void setFontSize(float fontSize);
        void setSpacing(float spacing);
        void setColor(raylib::Color color);

        struct MultiColor {
            std::string str;
            raylib::Color color = raylib::Color::White();
        };

        static void drawMultiColorStrs(
            Text2D &text, const std::vector<MultiColor> &strs);

        [[nodiscard]] raylib::Vector2 getSize() const;

    private:
        std::optional<std::reference_wrapper<raylib::Font>> _font;
        std::string _str;
        float _fontSize = 0;
        float _spacing = 0;
        raylib::Color _color = raylib::Color::Black();
    };

} // namespace Graphics

#endif
