/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Master
*/

#include "Master.hpp"
#include "Init.hpp"
#include "SfmlUtils.hpp"

namespace Zappy {
    Master::Master(int port, Clients &clients,
        std::unordered_map<std::string, std::size_t> &teams) :
        _window(sf::RenderWindow(sf::VideoMode(Init::WINDOW_SIZE_X,
                                     Init::WINDOW_SIZE_Y, Init::WINDOW_BITS),
            TITLE.data(), sf::Style::Close | sf::Style::Resize)),
        _view(
            sf::FloatRect(0.0, 0.0, Init::WINDOW_SIZE_X, Init::WINDOW_SIZE_Y)),
        _font(SfmlUtils::SfmlUtils::loadFromFile(FONT.data())),
        _process(port, clients),
        _toolBar(_font, port, _process, clients),
        _aiDescription(_font, _ais),
        _teamsInfo(_font, _ais, _process, teams),
        _clients(clients),
        _teams(teams)
    {
        _window.setFramerateLimit(Init::FPS);
        _window.setView(_view);
        _rec.setSize({Init::WINDOW_SIZE_X, Init::WINDOW_SIZE_Y});
        _rec.setFillColor(Init::PALEGREY);
        _window.setFramerateLimit(Init::FPS);
    }

    bool Master::update()
    {
        bool value = false;
        if (_window.isOpen()) {
            event();
            _window.clear(sf::Color::Black);
            _window.setView(_view);
            _window.draw(_rec);
            _teamsInfo.draw(_window);
            _aiDescription.draw(_window);
            _toolBar.draw(_window);
            _window.display();
            value = true;
        }
        return value;
    }

    void Master::event()
    {
        sf::Event event;
        sf::Vector2f mousePos =
            _window.mapPixelToCoords(sf::Mouse::getPosition(_window));
        while (_window.pollEvent(event)) {
            handleResize(event);
            _toolBar.event(event, mousePos);
            _aiDescription.event(event, mousePos);
            _teamsInfo.event(event, mousePos);
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed &&
                    event.key.code == sf::Keyboard::Escape))
                _window.close();
        }
    }

    void Master::handleResize(sf::Event event)
    {
        if (event.type != sf::Event::Resized)
            return;
        const auto gameW = static_cast<float>(Init::WINDOW_SIZE_X);
        const auto gameH = static_cast<float>(Init::WINDOW_SIZE_Y);
        auto windowRatio = static_cast<float>(_window.getSize().x) /
            static_cast<float>(_window.getSize().y);
        float viewRatio = gameW / gameH;
        sf::Vector2f size = {1, 1};
        sf::Vector2f pos = {0, 0};

        if (windowRatio >= viewRatio) {
            size.x = viewRatio / windowRatio;
            pos.x = (1.0f - size.x) / 2.0f;
        } else {
            size.y = windowRatio / viewRatio;
            pos.y = (1.0f - size.y) / 2.0f;
        }
        _view.setViewport(sf::FloatRect(pos.x, pos.y, size.x, size.y));
        _window.setView(_view);
    }

    const std::map<std::string, std::string> Master::_ais = {
        {"survivor", "Take food on his path"},
        {"layer", "Lays eggs around the map"},
        {"randomizer", "Take fully random decisions"},
        {"worker", "Take every stones it find"},
        {"ejector", "Seek players and push them"},
    };
} // namespace Zappy
