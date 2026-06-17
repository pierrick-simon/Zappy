/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** StateButton
*/

#ifndef STATEBUTTON_HPP
    #define STATEBUTTON_HPP

    #include <vector>
    #include "AButton.hpp"
    #include "SfmlUtils.hpp"

namespace SfmlUtils {
    template<typename T>
    class StateButton : public AButton {
    public:
        struct Texture {
            T type;
            std::reference_wrapper<sf::Texture> texture;
            sf::Color color = sf::Color::White;

            Texture(T t, sf::Texture &tex, sf::Color c = sf::Color::White) :
                type(t), texture(tex), color(c) {};
        };

        StateButton(std::vector<Texture> textures) :
            AButton(ButtonType::State), _textures(std::move(textures))
        {
            _sprite.setTexture(_textures[_id].texture.get());
            sf::Vector2u tmp = _textures[_id].texture.get().getSize();
            _sprite.setScale(_size.x / float(tmp.x), _size.y / float(tmp.y));
            _sprite.setPosition(_pos);
            setBound(_sprite.getGlobalBounds());
        }

        void setPos(sf::Vector2f pos)
        {
            _pos = pos;
            _sprite.setPosition(_pos);
        }

        void setSize(sf::Vector2f size)
        {
            _size = size;
            sf::Vector2u tmp = _textures[_id].texture.get().getSize();
            _sprite.setScale(_size.x / float(tmp.x), _size.y / float(tmp.y));
            setBound(_sprite.getGlobalBounds());
        }

        void draw(sf::RenderWindow &win) override
        {
            if (_hover)
                _sprite.setColor(
                    SfmlUtils::colorOffset(_textures[_id].color, -50));
            else
                _sprite.setColor(_textures[_id].color);
            win.draw(_sprite);
        }

        void func() override
        {
            _id++;
            if (_id >= _textures.size())
                _id = 0;
            _sprite.setTexture(_textures[_id].texture.get());
            sf::Vector2u size = _textures[_id].texture.get().getSize();
            _sprite.setScale(_size.x / float(size.x), _size.y / float(size.y));
        }

        void setState(T t)
        {
            for (std::size_t i = 0; i < _textures.size(); i++) {
                if (t == _textures[i].type) {
                    _id = i;
                    _sprite.setTexture(_textures[_id].texture.get());
                    sf::Vector2u size = _textures[_id].texture.get().getSize();
                    _sprite.setScale(
                        _size.x / float(size.x), _size.y / float(size.y));
                    break;
                }
            }
        }

        void reset()
        {
            _id = 0;
            _sprite.setTexture(_textures[_id].texture.get());
            sf::Vector2u size = _textures[_id].texture.get().getSize();
            _sprite.setScale(_size.x / float(size.x), _size.y / float(size.y));
        }

        T getState()
        {
            return _textures[_id].type;
        }

    private:
        sf::Vector2f _pos = {0, 0};
        sf::Vector2f _size = {0, 0};
        std::size_t _id = 0;
        std::vector<Texture> _textures;
        sf::Sprite _sprite;
    };
} // namespace SfmlUtils

#endif
