/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Window.hpp"

#include "raylib.hpp"

namespace Graphics {
    Window::Window()
    {
        InitWindow(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_TITLE);
        SetTargetFPS(TARGET_FPS);
    }
    Window::~Window()
    {
        CloseWindow();
    }

    void Window::update()
    {
        this->handleEvents();
        this->_scene.draw();
    }

    bool Window::isRunning()
    {
        return WindowShouldClose();
    }

    Scene &Window::getScene()
    {
        return this->_scene;
    }

    void Window::close()
    {
        CloseWindow();
    }

    void Window::handleEvents()
    {
        for (const auto &[key, method] : KEY_METHODS) {
            if (IsKeyPressed(key))
                method(*this);
        }
    }

    const std::unordered_map<::KeyboardKey, std::function<void(Window &)>>
        Window::KEY_METHODS = {{KEY_P, [](Window &) { close(); }}};

} // namespace Graphics
