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

namespace Graphics {
    class Scene : public Drawable {
    public:
        Scene();

        raylib::Camera &getCamera();
        [[nodiscard]] const raylib::Camera &getCamera() const;

        template<typename GameObjectType>
        std::unique_ptr<GameObject> &addObject(
            std::unique_ptr<GameObjectType> gameObject)
        {
            return this->_objects.emplace_back(std::move(gameObject));
        }

        void draw() const override;

    private:
        static constexpr raylib::Vector3 CAMERA_POS = {200, 200, 0};
        static constexpr raylib::Vector3 CAMERA_TARGET = Vector3::ZERO;
        std::vector<std::unique_ptr<GameObject>> _objects;
        raylib::Camera _camera {CAMERA_POS};
    };
} // namespace Graphics

#endif
