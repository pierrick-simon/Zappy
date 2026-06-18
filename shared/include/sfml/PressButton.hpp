/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** PressButton
*/

#ifndef PRESSBUTTON_HPP
    #define PRESSBUTTON_HPP

    #include "AButton.hpp"
    #include "SfmlUtils.hpp"

namespace SfmlUtils {
    class PressButton : public AButton {
    public:
        PressButton(sf::Font &font, unsigned int textSize, std::string str,
            sf::Color color = sf::Color::White);

        void draw(sf::RenderWindow &win) override;
        void func() override;

        void setPos(sf::Vector2f pos);
        void setSize(sf::Vector2f size);

        void reset()
        {
            _push = false;
        }

        [[nodiscard]] bool getPush() const
        {
            return _push;
        }

    private:
        sf::Vector2f _pos;
        sf::Vector2f _size;
        sf::RectangleShape _rec;
        sf::Text _text;
        unsigned int _textSize;
        std::string _str;
        sf::Color _color;
        bool _push = false;
    };
} // namespace SfmlUtils

#endif
