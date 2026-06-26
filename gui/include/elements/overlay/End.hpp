/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** End
*/

#ifndef END_HPP_
    #define END_HPP_

    #include <map>
    #include "Init.hpp"
    #include "graphics/IDrawable2D.hpp"
    #include "graphics/IEvent.hpp"
    #include "graphics/primitives/Box2D.hpp"
    #include "graphics/primitives/Text2D.hpp"

namespace Zappy {
    class End : public Graphics::IDrawable2D, public Graphics::IEvent {
    public:
        End(raylib::Font &font, std::map<std::string, raylib::Color> &teams,
            bool &quit);

        void draw2D() const override;
        void win(const std::string &team);
        void event(raylib::Camera3D &camera, const raylib::Vector2 &mouse,
            const Ray &ray, bool &leftClick) override;

    private:
        void initText(raylib::Font &font);
        void initButton(raylib::Font &font);

        Graphics::Box2D _box;
        Graphics::Box2D _button;
        Graphics::Text2D _text;
        Graphics::Text2D _team;
        Graphics::Text2D _buttonText;

        std::map<std::string, raylib::Color> &_teams;
        bool &_quit;

        static constexpr raylib::Vector2 SIZE = {600, 220};
        static constexpr raylib::Vector2 START_POS = {
            (Init::WINDOW_SIZE_X - SIZE.x) / 2.f,
            (Init::WINDOW_SIZE_Y - SIZE.y) / 2.f};
        static constexpr float TEXT_SIZE = 40.f;
        static constexpr raylib::Vector2 BUTTON_SIZE = {
            200, TEXT_SIZE + Init::GAP * 2.f};
        static constexpr raylib::Vector2 BUTTON_POS = {
            (Init::WINDOW_SIZE_X - BUTTON_SIZE.x) / 2.f,
            START_POS.y + SIZE.y - BUTTON_SIZE.y - Init::GAP * 2.f};
    };
} // namespace Zappy

#endif /* !END_HPP_ */
