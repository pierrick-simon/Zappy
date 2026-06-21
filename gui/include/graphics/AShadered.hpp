/*
** EPITECH PROJECT, 2026
** Zappy
** File description:
** DESCRIPTION
*/

#ifndef ASHADERED_HPP
    #define ASHADERED_HPP
    #include <optional>

#include "graphics/IShadered.hpp"

namespace Graphics {
    class AShadered : public IShadered {
    public:
        ::Shader asShader() const;
        Shader &getShader() override;
        [[nodiscard]] const Shader &getShader() const override;
        void setShader(Shader &shader) override;

    protected:
        std::optional<std::reference_wrapper<Shader>> _shader;
    };
} // namespace Graphics

#endif
