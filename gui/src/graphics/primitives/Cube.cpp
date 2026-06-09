/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Cube.hpp"

#include <SFML/OpenGL.hpp>

#include "OpenGLUtils.hpp"

namespace Graphics {
    void Cube::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        const double sx = DEFAULT_SIZE * this->getScale().getX();
        const double sy = DEFAULT_SIZE * this->getScale().getY();
        const double sz = DEFAULT_SIZE * this->getScale().getZ();

        glPushMatrix();
        glTranslated(VEC_TO_LIST(this->getPosition()));
        glMultMatrixd(this->getRotation().toGlMatrix().data());

        glColor3f(1.f, 0.f, 0.f);
        glBegin(GL_TRIANGLES);

        glVertex3d(-sx, -sy, sz);
        glVertex3d(sx, -sy, sz);
        glVertex3d(sx, sy, sz);
        glVertex3d(-sx, -sy, sz);
        glVertex3d(sx, sy, sz);
        glVertex3d(-sx, sy, sz);

        glVertex3d(sx, -sy, -sz);
        glVertex3d(-sx, -sy, -sz);
        glVertex3d(-sx, sy, -sz);
        glVertex3d(sx, -sy, -sz);
        glVertex3d(-sx, sy, -sz);
        glVertex3d(sx, sy, -sz);

        glVertex3d(-sx, -sy, -sz);
        glVertex3d(-sx, -sy, sz);
        glVertex3d(-sx, sy, sz);
        glVertex3d(-sx, -sy, -sz);
        glVertex3d(-sx, sy, sz);
        glVertex3d(-sx, sy, -sz);

        glVertex3d(sx, -sy, sz);
        glVertex3d(sx, -sy, -sz);
        glVertex3d(sx, sy, -sz);
        glVertex3d(sx, -sy, sz);
        glVertex3d(sx, sy, -sz);
        glVertex3d(sx, sy, sz);

        glVertex3d(-sx, sy, sz);
        glVertex3d(sx, sy, sz);
        glVertex3d(sx, sy, -sz);
        glVertex3d(-sx, sy, sz);
        glVertex3d(sx, sy, -sz);
        glVertex3d(-sx, sy, -sz);

        glVertex3d(-sx, -sy, -sz);
        glVertex3d(sx, -sy, -sz);
        glVertex3d(sx, -sy, sz);
        glVertex3d(-sx, -sy, -sz);
        glVertex3d(sx, -sy, sz);
        glVertex3d(-sx, -sy, sz);

        glEnd();
        glPopMatrix();
    }
} // namespace Graphics
