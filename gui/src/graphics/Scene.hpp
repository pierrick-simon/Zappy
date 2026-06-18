/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef SCENE_HPP
    #define SCENE_HPP
    #include <memory>
    #include <raylib-cpp.hpp>
    #include <vector>

    #include "GameObject.hpp"
    #include "UtilsVector.hpp"
    #include "graphics/Camera.hpp"
#include "graphics/UiObject.hpp"

namespace Graphics {
    class Scene {
    public:
        Scene();

        raylib::Camera &getCamera();
        [[nodiscard]] const raylib::Camera &getCamera() const;
        void update(float dt);
        void drawUiObjects() const;

        template<std::derived_from<GameObject> GameObjectType>
        std::unique_ptr<GameObjectType> &addObject(
            std::unique_ptr<GameObjectType> gameObject)
        {
            return reinterpret_cast<std::unique_ptr<GameObjectType> &>(
                this->_gameObjects.emplace_back(std::move(gameObject)));
        }

        template<std::derived_from<UIObject> UiObjectType>
        std::unique_ptr<UiObjectType> &addObject(
            std::unique_ptr<UiObjectType> gameObject)
        {
            return reinterpret_cast<std::unique_ptr<UiObjectType> &>(
                this->_uiObjects.emplace_back(std::move(gameObject)));
        }

        void drawGameObjects() const;

    private:
        static constexpr raylib::Vector3 CAMERA_POS = {200, 200, 0};
        static constexpr raylib::Vector3 CAMERA_TARGET = Vector3::ZERO;
        std::vector<std::unique_ptr<GameObject>> _gameObjects {};
        std::vector<std::unique_ptr<UIObject>> _uiObjects {};
        Camera _camera {CAMERA_POS};
    };
} // namespace Graphics

#endif
