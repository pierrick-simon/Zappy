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

namespace Zappy {
    class Environement;
}

namespace Graphics {
    class Scene {
    public:
        Scene() = default;

        raylib::Camera &getCamera();
        [[nodiscard]] const raylib::Camera &getCamera() const;
        void update(float dt);
        void drawUiObjects() const;

        template<std::derived_from<IObject> GameObjectType>
        void addObject(GameObjectType &gameObject)
        {
            this->_objects.emplace_back(gameObject);
        }

        void drawGameObjects() const;

    private:
        static constexpr raylib::Vector3 CAMERA_POS = {200, 200, 0};
        static constexpr raylib::Vector3 CAMERA_TARGET = Vector3::ZERO;
        [[deprecated]] std::vector<std::unique_ptr<GameObject>> _gameObjects {};
        [[deprecated]] std::vector<std::unique_ptr<UiObject>> _uiObjects {};
        std::vector<std::reference_wrapper<IObject>> _objects;
        Camera _camera {CAMERA_POS};
    };
} // namespace Graphics

#endif
