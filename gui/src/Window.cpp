/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Window.hpp"
#include <raylib-cpp.hpp>
#include "Assets.hpp"

namespace Graphics {
    Window::Window() :
        raylib::Window(
            WINDOW_SIZE_X, WINDOW_SIZE_Y, WINDOW_TITLE, 0, LOG_WARNING)
    {
        int monitor = GetCurrentMonitor();
        int W = GetMonitorWidth(monitor);
        int H = GetMonitorHeight(monitor);
        SetWindowSize(W, H);
        SetWindowPosition(0, 0);
        ToggleFullscreen();
        this->SetTargetFPS(TARGET_FPS);
        this->_scene.getCamera().SetPosition(DEFAULT_CAMERA_POS);
        _renderTarget = LoadRenderTexture(WINDOW_SIZE_X, WINDOW_SIZE_Y);
        SetTextureFilter(_renderTarget.texture, TEXTURE_FILTER_BILINEAR);
    }

    void Window::update()
    {
        this->handleEvents();
        this->_scene.update(GetFrameTime());
        updateTexture();
        draw();
    }

    void Window::updateTexture()
    {
        BeginTextureMode(_renderTarget);
        ClearBackground(BLACK);
        this->getScene().getCamera().BeginMode();

        this->_scene.drawSkyBox();

        this->getScene().getShader().BeginMode();
        this->_scene.drawGameObjects();
        this->getScene().getShader().EndMode();

        this->getScene().getCamera().EndMode();
        this->_scene.drawUiObjects();
        EndTextureMode();
    }

    void Window::draw()
    {
        this->BeginDrawing();
        ClearBackground(raylib::Color::Black());
        auto scaleX = float(GetScreenWidth()) / WINDOW_SIZE_X;
        auto scaleY = float(GetScreenHeight()) / WINDOW_SIZE_Y;
        auto scale = std::min(scaleX, scaleY);
        Rectangle src = {0, 0, float(WINDOW_SIZE_X), -float(WINDOW_SIZE_Y)};
        Rectangle dst = {
            (float(GetScreenWidth()) - WINDOW_SIZE_X * scale) / 2.0f,
            (float(GetScreenHeight()) - WINDOW_SIZE_Y * scale) / 2.0f,
            WINDOW_SIZE_X * scale,
            WINDOW_SIZE_Y * scale};
        DrawTexturePro(_renderTarget.texture,
            src,
            dst,
            {0, 0},
            0.0f,
            raylib::Color::White());
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
        _scene.event();
    }

    const std::unordered_map<::KeyboardKey, std::function<void(Window &)>>
        Window::KEY_METHODS = {};

} // namespace Graphics
