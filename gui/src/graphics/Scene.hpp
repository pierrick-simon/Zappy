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
    #include "graphics/IShadered.hpp"
    #include "graphics/Shader.hpp"
    #include "graphics/SkyBox.hpp"
    #include "graphics/UiObject.hpp"
    #include "graphics/primitives/Model.hpp"

namespace Zappy {
    class Environement;
}

namespace Graphics {
    class Scene {
    public:
        Scene();

        raylib::Camera &getCamera();
        [[nodiscard]] const raylib::Camera &getCamera() const;
        void update(float dt);
        void drawUiObjects() const;
        void event();

        template<std::derived_from<IObject> GameObjectType>
        void addObject(GameObjectType &gameObject)
        {
            try {
                auto &model = dynamic_cast<Model &>(gameObject);
                this->setShaderForModel(model);
            } catch (std::bad_cast &) {
            }
            try {
                auto &shadered = dynamic_cast<IShadered &>(gameObject);
                shadered.setShader(this->_shader);
            } catch (std::bad_cast &) {
            }
            this->_objects.emplace_back(gameObject);
        }

        void drawSkyBox() const;
        void drawGameObjects() const;

        void setShaderForModels() const;
        void setShaderForModel(const Model &model) const;
        Shader &getShader();

    private:
        static constexpr raylib::Vector3 CAMERA_POS = {200, 200, 0};
        static constexpr raylib::Vector3 CAMERA_TARGET = Vector3::ZERO;
        static const std::string FRAGMENT_SHADER_PATH;
        static const std::string VERTEX_SHADER_PATH;

        [[deprecated]] std::vector<std::unique_ptr<GameObject>> _gameObjects {};
        [[deprecated]] std::vector<std::unique_ptr<UiObject>> _uiObjects {};
        std::vector<std::reference_wrapper<IObject>> _objects;
        Camera _camera {CAMERA_POS};

        Shader _shader;
        SkyBox _skyBox;
    };
} // namespace Graphics

#endif
