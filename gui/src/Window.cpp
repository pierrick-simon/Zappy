/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Window.hpp"

#include "Assets.hpp"
#include "UtilsVector.hpp"
#include "graphics/primitives/Model.hpp"
#include "raylib.hpp"

namespace Graphics {
    Window::Window() :
        raylib::Window(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_TITLE)
    {
        this->SetTargetFPS(TARGET_FPS);

    }

    void Window::update()
    {
        this->handleEvents();
        this->BeginDrawing();
        this->ClearBackground(raylib::Color::RayWhite());
        this->getScene().getCamera().BeginMode();
        this->_scene.draw();
        this->getScene().getCamera().EndMode();
        this->EndDrawing();
    }

    bool Window::isRunning()
    {
        return !WindowShouldClose();
    }

    Scene &Window::getScene()
    {
        return this->_scene;
    }


    void Window::handleEvents()
    {
        for (const auto &[key, method] : KEY_METHODS) {
            if (IsKeyPressed(key))
                method(*this);
        }
    }

    const std::unordered_map<::KeyboardKey, std::function<void(Window &)>>
        Window::KEY_METHODS = {{KEY_P, [](Window &) { Close(); }}};

} // namespace Graphics
