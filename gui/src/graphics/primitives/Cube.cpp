/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Cube.hpp"

#include <SFML/OpenGL.hpp>

namespace Graphics {
    void Cube::draw(sf::RenderTarget &target, sf::RenderStates states) const
    {
        glPushMatrix();
        this->applyTransform();

        glColor3f(1.f, 0.f, 0.f);
        glBegin(GL_TRIANGLES);

        glVertex3d(-DEFAULT_SIZE, -DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, -DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, -DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);

        glVertex3d(DEFAULT_SIZE, -DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, -DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, -DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, DEFAULT_SIZE, -DEFAULT_SIZE);

        glVertex3d(-DEFAULT_SIZE, -DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, -DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, -DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, DEFAULT_SIZE, -DEFAULT_SIZE);

        glVertex3d(DEFAULT_SIZE, -DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, -DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, -DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);

        glVertex3d(-DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, DEFAULT_SIZE, -DEFAULT_SIZE);

        glVertex3d(-DEFAULT_SIZE, -DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, -DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, -DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, -DEFAULT_SIZE, -DEFAULT_SIZE);
        glVertex3d(DEFAULT_SIZE, -DEFAULT_SIZE, DEFAULT_SIZE);
        glVertex3d(-DEFAULT_SIZE, -DEFAULT_SIZE, DEFAULT_SIZE);

        glEnd();
        glPopMatrix();
    }
} // namespace Graphics
