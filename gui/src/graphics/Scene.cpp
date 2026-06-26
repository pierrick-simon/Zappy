/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Scene.hpp"

#include "Assets.hpp"
#include "Tile.hpp"
#include "graphics/IDrawable2D.hpp"
#include "graphics/IEvent.hpp"
#include "graphics/primitives/Model.hpp"

namespace Graphics {

    Scene::Scene() :
        _shader(VERTEX_SHADER_PATH, FRAGMENT_SHADER_PATH), _skyBox()
    {
        this->_shader.setValue("sunDirection",
            static_cast<const ::Vector3>(
                raylib::Vector3 {-0.7f, -1.0f, -0.4f}.Normalize()));
        this->_shader.setValue("sunColor", ::Vector3 {1, 0.95f, 0.85f});
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
        for (auto &object : this->_objects) {
            try {
                auto &updatable = dynamic_cast<IUpdatable &>(object.get());
                updatable.update(dt);
            } catch (std::bad_cast &) {
            }
        }
        this->_shader.setValue("cameraPos", this->getCamera().GetPosition());
    }

    void Scene::drawUiObjects() const
    {
        for (auto &object : this->_objects) {
            try {
                auto &uiObject = dynamic_cast<IDrawable2D &>(object.get());
                uiObject.draw2D();
            } catch (std::bad_cast &) {
            }
        }
    }

    void Scene::drawSkyBox() const
    {
        _skyBox.draw3D();
    }

    void Scene::drawGameObjects() const
    {
        for (auto &object : this->_objects) {
            try {
                auto &gameObject = dynamic_cast<IDrawable3D &>(object.get());
                gameObject.draw3D();
            } catch (std::bad_cast &) {
            }
        }
    }

    void Scene::setShaderForModels() const
    {
        for (auto &object : this->_objects) {
            try {
                auto &gameObject = dynamic_cast<Model &>(object.get());
                this->setShaderForModel(gameObject);
            } catch (std::bad_cast &) {
            }
        }
    }

    void Scene::setShaderForModel(const Model &model) const
    {
        model.materials[0].shader = this->_shader.asShader();
    }

    Shader &Scene::getShader()
    {
        return this->_shader;
    }

    void Scene::event()
    {
        raylib::Vector2 mouse = raylib::Mouse::GetPosition();
        raylib::Ray ray = _camera.GetMouseRay(mouse);
        bool click = raylib::Mouse::IsButtonPressed(MOUSE_LEFT_BUTTON);
        for (auto &object : this->_objects) {
            try {
                auto &gameObject = dynamic_cast<IEvent &>(object.get());
                gameObject.event(_camera, mouse, ray, click);
            } catch (std::bad_cast &) {
            }
        }
    }

    const std::string Scene::FRAGMENT_SHADER_PATH =
        Assets::getResource("shaders/sun.fs");
    const std::string Scene::VERTEX_SHADER_PATH =
        Assets::getResource("shaders/sun.vs");
} // namespace Graphics
