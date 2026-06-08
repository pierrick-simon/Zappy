/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Scene.hpp"

namespace Graphics {

    void Scene::render() const
    {
        for (const auto &object : this->_objects)
            object->render();
    }

    Camera &Scene::getCamera()
    {
        return this->_camera;
    }

    const Camera &Scene::getCamera() const
    {
        return this->_camera;
    }
} // Graphics
