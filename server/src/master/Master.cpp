/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** Master
*/

#include "Master.hpp"
#include "SfmlUtils.hpp"

namespace Zappy {
    Master::Master(int port, Clients &clients,
        std::unordered_map<std::string, std::size_t> &teams) :
        _window(sf::RenderWindow(
            sf::VideoMode(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_BITS),
            "Zappy Server", sf::Style::Close | sf::Style::Resize)),
        _view(sf::FloatRect(0.0, 0.0, WINDOW_SIZE_X, WINDOW_SIZE_Y)),
        _font(SfmlUtils::SfmlUtils::loadFromFile(FONT.data())),
        _port(port),
        _clients(clients),
        _teams(teams)
    {
        _window.setFramerateLimit(FPS);
        _window.setView(_view);
        _rec.setSize({WINDOW_SIZE_X, WINDOW_SIZE_Y});
        _rec.setFillColor(BACKGROUND_COLOR);
        _window.setFramerateLimit(FPS);
    }

    void Master::addGui()
    {
        if (_clients.gui.empty())
            _process.add(GUI_EXEC.data(), {"-p", std::to_string(_port)});
    }

    bool Master::update()
    {
        bool value = false;
        if (_window.isOpen()) {
            event();
            _window.clear(sf::Color::Black);
            _window.setView(_view);
            _window.draw(_rec);
            _window.display();
            value = true;
        }
        return value;
    }

    void Master::event()
    {
        sf::Event event;
        while (_window.pollEvent(event)) {
            handleResize(event);
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
        const auto gameW = static_cast<float>(WINDOW_SIZE_X);
        const auto gameH = static_cast<float>(WINDOW_SIZE_Y);
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
} // namespace Zappy
