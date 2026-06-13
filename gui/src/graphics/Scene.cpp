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
        this->_camera.Update(CAMERA_THIRD_PERSON);
    }
    raylib::Camera &Scene::getCamera()
    {
        return this->_camera;
    }

    const raylib::Camera &Scene::getCamera() const
    {
        return this->_camera;
    }

    void Scene::draw() const
    {
        for (auto &object : this->_objects)
            object->draw();
    }
} // namespace Graphics
