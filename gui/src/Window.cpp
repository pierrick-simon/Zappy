/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Window.hpp"

#include "Assets.hpp"
#include "graphics/primitives/Model.hpp"
#include "raylib.hpp"

namespace Graphics {
    Window::Window() :
        raylib::Window(WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_TITLE, 0, LOG_ALL)
    {
        this->SetTargetFPS(TARGET_FPS);
        this->_scene.getCamera().SetPosition({200, 200, 0});
        this->_scene.getCamera().SetTarget({0, 0, 0});
        this->addObject<Model>(Assets::GetResource(
            "map/Low_Poly_Low_Poly_Mill_obj/low-poly-mill.obj")); // Todo:
                                                                  // remove
    }

    void Window::update()
    {
        this->handleEvents();
        this->_scene.update();
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
