/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "graphics/AShadered.hpp"

namespace Graphics {

    Shader &AShadered::getShader()
    {
        return this->_shader.value();
    }

    const Shader &AShadered::getShader() const
    {
        return this->_shader.value();
    }
    void AShadered::setShader(Shader &shader)
    {
        this->_shader = shader;
    }
} // namespace Graphics
