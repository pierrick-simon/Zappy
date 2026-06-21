/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#include "Shader.hpp"

#include <iostream>

namespace Graphics {
    void Shader::setValue(const std::string &name, const ::Vector3 &vector)
    {
        float values[3] = {vector.x, vector.y, vector.z};
        this->setValue(name, values, SHADER_UNIFORM_VEC3);
    }

    void Shader::setValue(const std::string &name, const ::Vector4 &vector)
    {
        float values[4] = {vector.x, vector.y, vector.z, vector.w};

        this->setValue(name, values, SHADER_UNIFORM_VEC4);
    }

    int Shader::getLocation(const std::string &name)
    {
        if (!this->_locations.contains(name))
            this->_locations[name] = this->GetLocation(name);
        return this->_locations[name];
    }
} // namespace Graphics
