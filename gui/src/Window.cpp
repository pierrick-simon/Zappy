/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Window.hpp"

#include "Assets.hpp"
#include "graphics/primitives/Model.hpp"
#include "raylib-cpp.hpp"

namespace Graphics {
    Window::Window() :
        raylib::Window(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_TITLE, 0, LOG_ALL)
    {
        this->SetTargetFPS(TARGET_FPS);
    }

    void Window::update()
    {
        this->handleEvents();
        this->_scene.update(this->GetFrameTime());
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
        for (auto key =
                 static_cast<KeyboardKey>(raylib::Keyboard::GetKeyPressed());
            key != 0;
            key = static_cast<KeyboardKey>(raylib::Keyboard::GetKeyPressed())) {
            auto it = KEY_METHODS.find(key);
            if (it != KEY_METHODS.end())
                it->second(*this);
        }
    }

    const std::unordered_map<::KeyboardKey, std::function<void(Window &)>>
        Window::KEY_METHODS = {{KEY_P, [](Window &) { Close(); }}};

} // namespace Graphics
