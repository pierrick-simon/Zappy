/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Scene.hpp"

#include "graphics/IDrawable2D.hpp"

namespace Graphics {

    raylib::Camera &Scene::getCamera()
    {
        return this->_camera;
    }

    const raylib::Camera &Scene::getCamera() const
    {
        return this->_camera;
    }

    void Scene::update(float dt)
    {
        this->_camera.update(dt);
        for (auto &object : this->_objects) {
            try {
                auto &updatable = dynamic_cast<IUpdatable &>(object.get());
                updatable.update(dt);
            } catch (std::bad_cast &) {
            }
        }
    }

    void Scene::drawUiObjects() const
    {
        for (auto &object : this->_objects) {
            try {
                auto &uiObject = dynamic_cast<IDrawable2D &>(object.get());
                uiObject.draw();
            } catch (std::bad_cast &) {
            }
        }
    }

    void Scene::drawGameObjects() const
    {
        for (auto &object : this->_objects) {
            try {
                auto &gameObjecte = dynamic_cast<IDrawable3D &>(object.get());
                gameObjecte.draw();
            } catch (std::bad_cast &) {
            }
        }
    }
} // namespace Graphics
