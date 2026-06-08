/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef SCENE_HPP
    #define SCENE_HPP
    #include <memory>
    #include <vector>

    #include "Camera.hpp"
    #include "IGameObject.hpp"

namespace Graphics
{
    class Scene
    {
    public:
        explicit Scene(sf::RenderWindow &window)
            : _camera(window)
        {
        }

        void updateGl() const;
        void render() const;
        Camera &getCamera();
        [[nodiscard]] const Camera &getCamera() const;

        template<typename GameObjectType>
        std::unique_ptr<IGameObject> &addObject(std::unique_ptr<GameObjectType> gameObject)
        {
            return this->_objects.emplace_back(std::move(gameObject));
        }
    private:
        std::vector<std::unique_ptr<IGameObject>> _objects;
        Camera _camera;
    };
} // Graphics

#endif
