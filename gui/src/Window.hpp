/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef WINDOW_HPP
    #define WINDOW_HPP
    #include <functional>
    #include <unordered_map>
#include "raylib.hpp"

    #include "graphics/Scene.hpp"

namespace Graphics {
    class Window {
    public:
        Window();
        ~Window();
        void update();
        [[nodiscard]] static bool isRunning();

        Scene &getScene();
        static void close();

        template<typename GameObjectType, typename... Args>
        std::unique_ptr<GameObject> &addObject(Args &&...args)
        {
            return this->getScene().addObject(
                std::move(std::make_unique<GameObjectType>(args...)));
        }

    private:
        void handleEvents();

        Scene _scene;

        static const std::unordered_map<::KeyboardKey,
            std::function<void(Window &)>>
            KEY_METHODS;

        static constexpr unsigned int WINDOW_SIZE_X = 1920;
        static constexpr unsigned int WINDOW_SIZE_Y = 1080;
        static constexpr auto TARGET_FPS = 60;
        static constexpr auto WINDOW_TITLE = "Zappy GUI";
        static constexpr auto FOV = 60.0;
        static constexpr auto NEAR_PLANE = 0.001;
        static constexpr auto FAR_PLANE = 500.0;
    };
} // namespace Graphics

#endif
