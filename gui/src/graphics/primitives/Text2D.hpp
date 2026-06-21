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
    #include "Text.hpp"
    #include "graphics/UiObject.hpp"

namespace Graphics {

    class Text2D : public UiObject {
    public:
        Text2D() = default;
        void draw2D() const override;

        void setFont(Font &font);
        void setStr(std::string str);
        void setOrigin(Vector2 origin);
        void setFontSize(float fontSize);
        void setSpacing(float spacing);
        void setColor(Color color);

        [[nodiscard]] Vector2 getSize() const;

    private:
        std::optional<std::reference_wrapper<Font>> _font;
        std::string _str;
        Vector2 _origin = {0, 0};
        float _fontSize = 0;
        float _spacing = 0;
        Color _color = BLACK;
    };

} // namespace Graphics

#endif
