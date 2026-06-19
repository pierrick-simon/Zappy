/*
** EPITECH PROJECT, 2026
** gui
** File description:
** ResourceInfo
*/

#ifndef RESOURCEINFO_HPP_
    #define RESOURCEINFO_HPP_

    #include "graphics/IDrawable2D.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class ResourceInfo : public Graphics::IDrawable2D {
    public:
        ResourceInfo(Font &font, const Vector2 &pos);

        void draw2D() const override;
        void update(std::size_t map, std::size_t players);

    private:
        Vector2 _pos;
        Graphics::Text2D _text;
        Graphics::Box2D _rec;

        Font &_font;

        static constexpr std::size_t MAX = 9999999;
        static constexpr float FONTSIZE = 25;
    };
} // namespace Zappy

#endif /* !RESOURCEINFO_HPP_ */
