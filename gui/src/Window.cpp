/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/


#include "Window.hpp"

#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include <SFML/Window/Context.hpp>
#include <SFML/Window/Event.hpp>

#include "OpenGLUtils.hpp"

namespace Graphics {
    Window::Window() : RenderWindow(
                           sf::VideoMode(WINDOW_SIZE_X,
                                         WINDOW_SIZE_Y,
                                         WINDOW_BITS),
                           WINDOW_TITLE,
                           sf::Style::Default,
                           CONTEXT_SETTINGS), _scene(*this)
    {
        this->RenderWindow::setActive();
    }

    void Window::updateGl()
    {
        glDepthMask(GL_TRUE);
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(FOV,
                       this->getAspectRatio(),
                       NEAR_PLANE,
                       FAR_PLANE);
        glMatrixMode(GL_MODELVIEW);
        const Camera &camera = this->_scene.getCamera();
        auto &camPos = camera.getPosition();
        Maths::Vector3D cameraForward = camera.getForward() + camPos;
        gluLookAt(VEC_TO_LIST(camPos),
                  VEC_TO_LIST(cameraForward),
                  VEC_TO_LIST(Maths::UP));
        this->pushGLStates();
    }

    double Window::getAspectRatio() const
    {
        Maths::Vector2D size = Maths::Vector2D(this->getSize().x,
                                               this->getSize().y);
        return size.getX() / size.getY();
    }

    void Window::update()
    {
        this->updateGl();
        this->handleEvents();
        this->_scene.render();
        this->display();
        glGetError();
    }

    bool Window::isRunning() const
    {
        return this->isOpen();
    }

    Scene &Window::getScene()
    {
        return this->_scene;
    }

    void Window::handleEvents()
    {
        sf::Event event;

        while (this->pollEvent(event))
            if (EVENTS_METHODS.contains(event.type))
                EVENTS_METHODS.at(event.type)(*this, event);
    }

    const std::unordered_map<
        sf::Event::EventType, std::function<void
            (Window &, sf::Event &event)>> Window::EVENTS_METHODS = {
        {
            sf::Event::EventType::Closed,
            [](Window &win, sf::Event &) {
                win.close();
            }
        }
    };

    const sf::ContextSettings Window::CONTEXT_SETTINGS = sf::ContextSettings(24);

} // Graphics
