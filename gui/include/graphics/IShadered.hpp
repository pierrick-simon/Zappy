/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef ISHADERED_HPP
    #define ISHADERED_HPP
    #include "graphics/Shader.hpp"

namespace Graphics {
    class IShadered {
    public:
        virtual ~IShadered() = default;
        virtual Shader &getShader() = 0;
        virtual void setShader(Shader &shader) = 0;
        [[nodiscard]] virtual const Shader &getShader() const = 0;
    };
} // namespace Graphics
#endif
