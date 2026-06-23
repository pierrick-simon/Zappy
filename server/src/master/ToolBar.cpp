/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** ToolBar
*/

#include "ToolBar.hpp"
#include "Connect.hpp"
#include "Init.hpp"

namespace Zappy {
    ToolBar::ToolBar(
        sf::Font &font, int port, AddProcess &process, Clients &clients) :
        _playTexture(SfmlUtils::SfmlUtils::loadTextureFromFile(PLAY.data())),
        _pauseTexture(SfmlUtils::SfmlUtils::loadTextureFromFile(PAUSE.data())),
        _showTexture(SfmlUtils::SfmlUtils::loadTextureFromFile(SHOW.data())),
        _play({{PAUSE, _playTexture, sf::Color::Red},
            {PLAY, _pauseTexture, sf::Color::Green}}),
        _show({{NONE, _showTexture, sf::Color::Green},
            {SHOW, _showTexture, sf::Color::Red}}),
        _port(port),
        _clients(clients),
        _process(process)
    {
        _ip = Shared::Connect::getIp();
        _text.setFont(font);
        _text.setStyle(sf::Text::Bold);
        _text.setFillColor(sf::Color::Black);
        _text.setCharacterSize(Init::TITLE_SIZE);
        _rec.setSize({Init::WINDOW_SIZE_X, Init::TOOLBAR_SIZE_Y});
        _rec.setFillColor(Init::LIGHTGREY);
        _play.setPos({Init::WINDOW_SIZE_X - GAP - SIZE_PLAY_BUTTON, GAP});
        _play.setSize({SIZE_PLAY_BUTTON, SIZE_PLAY_BUTTON});
        _show.setPos(
            {Init::WINDOW_SIZE_X - (GAP + SIZE_PLAY_BUTTON) * 2.0 - GAP, GAP});
        _show.setSize({SIZE_PLAY_BUTTON, SIZE_PLAY_BUTTON});
    }

    void ToolBar::draw(sf::RenderWindow &win)
    {
        win.draw(_rec);
        _text.setStyle(sf::Text::Bold);
        _text.setFillColor(sf::Color::Black);
        _text.setString(std::string(PORT) + std::to_string(_port));
        sf::FloatRect rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.0f, rc.top + rc.height / 2.0f);
        _text.setPosition(
            Init::WINDOW_SIZE_X / 3.0f, Init::TOOLBAR_SIZE_Y / 2.0f);
        win.draw(_text);
        _text.setString(std::string(IP) + _ip);
        rc = _text.getLocalBounds();
        _text.setOrigin(rc.left + rc.width / 2.0f, rc.top + rc.height / 2.0f);
        _text.setPosition(
            Init::WINDOW_SIZE_X / 3.0f * 2.0f, Init::TOOLBAR_SIZE_Y / 2.0f);
        win.draw(_text);
        _play.draw(win);
        if (_clients.gui.empty())
            _show.setState(NONE);
        else
            _show.setState(SHOW);
        _show.draw(win);
    }

    void ToolBar::event(sf::Event &event, sf::Vector2f mousePos)
    {
        _play.click(mousePos, event);
        auto before = _show.getState();
        _show.click(mousePos, event);
        if (event.type == sf::Event::KeyPressed &&
            event.key.code == sf::Keyboard::Space) {
            if (_play.getState() == PLAY)
                _play.setState(PAUSE);
            else
                _play.setState(PLAY);
        }
        if (before == NONE && _show.getState() == SHOW)
            _process.addGui();
        _playing = _play.getState() == PLAY;
    }
} // namespace Zappy
