/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "GameObject.hpp"

#include <SFML/OpenGL.hpp>

#include "OpenGLUtils.hpp"

namespace Graphics {
    void GameObject::applyTransform() const
    {
        glTranslated(VEC_TO_LIST(this->getPosition()));
        glMultMatrixd(this->getRotation().toGlMatrix().data());
        glScaled(VEC_TO_LIST(this->getScale()));
    }
} // namespace Graphics
