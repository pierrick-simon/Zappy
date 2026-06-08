/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Scene.hpp"

#include <SFML/Graphics/RenderTarget.hpp>

namespace Graphics {

    void Scene::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        for (auto &object : this->_objects)
            target.draw(*object, states);
    }

    Camera &Scene::getCamera()
    {
        return this->_camera;
    }

    const Camera &Scene::getCamera() const
    {
        return this->_camera;
    }
} // namespace Graphics
