/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Scene.hpp"

namespace Graphics {
    Scene::Scene()
    {
        this->_camera.Update(CAMERA_CUSTOM);
    }
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
        for (auto &object : this->_gameObjects)
            object->update(dt);
        for (auto &object : this->_uiObjects)
            object->update(dt);
    }

    void Scene::drawUiObjects() const
    {
        for (auto &object : this->_uiObjects)
            object->draw();
    }

    void Scene::drawGameObjects() const
    {
        for (auto &object : this->_gameObjects)
            object->draw();
    }
} // namespace Graphics
