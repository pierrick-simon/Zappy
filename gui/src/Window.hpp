/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef WINDOW_HPP
    #define WINDOW_HPP
    #include <SFML/Graphics/RenderWindow.hpp>
    #include <SFML/Window/Event.hpp>
    #include <functional>
    #include <unordered_map>

    #include "graphics/Scene.hpp"

namespace Graphics {
    class Window : public sf::RenderWindow {
    public:
        Window();
        void updateGl();
        double getAspectRatio() const;
        void update();
        [[nodiscard]] bool isRunning() const;

        Scene &getScene();

        template<typename GameObjectType, typename... Args>
        std::unique_ptr<GameObject> &addObject(Args &&...args)
        {
            return this->getScene().addObject(
                std::move(std::make_unique<GameObjectType>(args...)));
        }

    private:
        void handleEvents();

        Scene _scene;

        static const std::unordered_map<sf::Event::EventType,
            std::function<void(Window &, sf::Event &event)>>
            EVENTS_METHODS;

        static constexpr unsigned int WINDOW_SIZE_X = 1920;
        static constexpr unsigned int WINDOW_SIZE_Y = 1080;
        static constexpr unsigned int WINDOW_BITS = 32;
        static constexpr auto WINDOW_TITLE = "Zappy GUI";
        static constexpr auto FOV = 60.0;
        static constexpr auto NEAR_PLANE = 0.001;
        static constexpr auto FAR_PLANE = 500.0;
        static const sf::ContextSettings CONTEXT_SETTINGS;
    };
} // namespace Graphics

#endif
