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
    #include "GameObject.hpp"

namespace Graphics {
    class Scene : public sf::Drawable {
    public:
        explicit Scene() = default;

        Camera &getCamera();
        [[nodiscard]] const Camera &getCamera() const;

        template<typename GameObjectType>
        std::unique_ptr<GameObject> &addObject(
            std::unique_ptr<GameObjectType> gameObject)
        {
            return this->_objects.emplace_back(std::move(gameObject));
        }

    protected:
        void draw(
            sf::RenderTarget &target, sf::RenderStates states) const override;

    private:
        std::vector<std::unique_ptr<GameObject>> _objects;
        Camera _camera;
    };
} // namespace Graphics

#endif
