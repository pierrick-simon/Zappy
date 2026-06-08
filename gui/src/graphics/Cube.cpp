/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Cube.hpp"

#include <SFML/OpenGL.hpp>

#include "OpenGLUtils.hpp"

namespace Graphics
{
    void Cube::glDraw() const
    {
        glBegin(GL_TRIANGLES);
        glColor3b(1, 0, 0);
        glTranslated(VEC_TO_LIST(this->getPosition()));
        double left = this->getPosition().getX() - DEFAULT_SIZE * this->getScale().getX();
        double right = this->getPosition().getX() + DEFAULT_SIZE * this->getScale().getX();
        double bottom = this->getPosition().getY() - DEFAULT_SIZE * this->getScale().getY();
        double top = this->getPosition().getY() + DEFAULT_SIZE * this->getScale().getY();
        double front = this->getPosition().getZ() - DEFAULT_SIZE * this->getScale().getZ();
        double back = this->getPosition().getZ() + DEFAULT_SIZE * this->getScale().getZ();

        glVertex3d(left, bottom, back);
        glVertex3d(left, bottom, front);
        glVertex3d(left, top, front);
        glVertex3d(left, top, back);
        glVertex3d(right, bottom, back);
        glVertex3d(right, bottom, front);
        glVertex3d(right, top, front);
        glVertex3d(right, top, back);
        glEnd();
    }
} // Graphics